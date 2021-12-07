/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
 * Thread.h
 *
 *  Created on: Nov 8, 2018
 *      Author: cgries
 */

#ifndef BASYX_ABSTRACTION_IMPL_UNIX_THREAD_THREAD_IMPL_H
#define BASYX_ABSTRACTION_IMPL_UNIX_THREAD_THREAD_IMPL_H

#include <pthread.h>

#define BASYX_THREAD_CALL_CONVENTION

namespace basyx {
namespace detail {

class thread_impl {
public:
    thread_impl(unsigned int (*)(void*), void*);
    ~thread_impl();

    int run();
    int join();
    int detach();

private:
    pthread_t threadDesc;
    unsigned int (*threadFn)(void*);
    void* threadArg;

public:
    static int getCurrentThreadId();
};

}
}

#endif /* BASYX_ABSTRACTION_IMPL_UNIX_THREAD_THREAD_IMPL_H */
