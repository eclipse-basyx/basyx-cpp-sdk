/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_ABSTRACTION_IMPL_THREAD_LAUNCHER_H
#define BASYX_ABSTRACTION_IMPL_THREAD_LAUNCHER_H

#define USE_STD_ATOMIC
//#define USE_STD_INVOKE
//#define USE_STD_DECAY_T

#include <BaSyx/util/meta.h>
#include <BaSyx/util/util.h>

#ifndef USE_STD_INVOKE
#include <BaSyx/util/invoke.h>
#endif

#ifdef USE_STD_ATOMIC
#include <atomic>
#endif

#ifdef _WIN32
#define BASYX_THREAD_CALL_CONVENTION __stdcall
#else
#define BASYX_THREAD_CALL_CONVENTION
#endif

namespace basyx {
namespace detail {

template <class Func, typename... Args>
class Thread_Launcher {
private:
#ifdef USE_STD_ATOMIC
    std::atomic_flag not_started_lock = ATOMIC_FLAG_INIT;
#else
    bool started = false;
#endif
private:
    struct target {
        util::decay_t<Func> f;
        std::tuple<util::decay_t<Args>...> args;

        template <class OtherFunc, typename... OtherArgs>
        target(OtherFunc&& f, OtherArgs&&... args)
            : f { std::forward<OtherFunc>(f) }
            , args { std::make_tuple<OtherArgs...>(std::forward<OtherArgs>(args)...) }
        {
        }

        inline void dispatch()
        {
            callFunc(typename util::meta::generator_sequence<sizeof...(Args)>::type());
        }

        template <int... tail>
        inline void callFunc(util::meta::sequence<tail...>)
        {
#ifdef USE_STD_INVOKE
            std::invoke(std::forward<util::decay_t<Func>>(f), std::get<tail>(args)...);
#else
            util::invoke(std::forward<util::decay_t<Func>>(f), std::get<tail>(args)...);
#endif
        }
    };

    std::unique_ptr<target> targetPtr;

private:
    static unsigned BASYX_THREAD_CALL_CONVENTION launch_internal(void* this_ptr)
    {
        auto _this = static_cast<Thread_Launcher<Func, Args...>*>(this_ptr);
        auto _target = std::forward<std::unique_ptr<target>>(_this->targetPtr);
#ifdef USE_STD_ATOMIC
        _this->not_started_lock.clear(std::memory_order_release);
#else
        _this->started = true;
#endif
        _target->dispatch();
        return 0;
    };

public:
    explicit Thread_Launcher(Func&& f, Args&&... args)
        : targetPtr { util::make_unique<target>(std::forward<Func>(f), std::forward<Args>(args)...) }
    {
#ifdef USE_STD_ATOMIC
        not_started_lock.test_and_set(std::memory_order_acquire);
#endif
    }

    template <typename T, typename D, template <typename, typename> class thrd_impl>
    inline void Launch(thrd_impl<T, D>& thrd)
    {
        thrd = util::make_unique<T>(Thread_Launcher<Func, Args...>::launch_internal, this);
        thrd->run();

        // spinlock until thread is started
#ifdef USE_STD_ATOMIC
        while (this->not_started_lock.test_and_set(std::memory_order_acquire))
#else
        while (!started)
#endif
        /* spin */   ; // do nothing
    };
};

}
}

#endif /* BASYX_ABSTRACTION_IMPL_THREAD_LAUNCHER_H */
