/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_ABSTRACTION_IMPL_WINDOWS_THREAD_THREAD_IMPL_H
#define BASYX_ABSTRACTION_IMPL_WINDOWS_THREAD_THREAD_IMPL_H

#include <process.h>
#include <windows.h>

namespace basyx {
namespace detail {

class thread_impl 
{
public:
    thread_impl(unsigned int(__stdcall*)(void*), void*);
    ~thread_impl();

    int run();
    int join();
    int detach();

private:
    HANDLE threadDesc;
    unsigned int threadID;
    unsigned int(__stdcall* threadFn)(void*);
    void* threadArg;

public:
    static int getCurrentThreadId();
};

}
}

#endif /* BASYX_ABSTRACTION_IMPL_WINDOWS_THREAD_THREAD_IMPL_H */
