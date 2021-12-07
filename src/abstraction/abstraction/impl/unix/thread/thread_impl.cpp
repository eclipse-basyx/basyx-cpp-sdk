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
 * Thread.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: gri
 */

#include <BaSyx/abstraction/impl/unix/thread/thread_impl.h>

namespace basyx {
namespace detail {

    /* For POSIX-style threads functions */
    thread_impl::thread_impl(unsigned int (*threadFn)(void*), void* threadArg)
    {
        this->threadFn = threadFn;
        this->threadArg = threadArg;
        this->threadDesc = 0;
    }

    thread_impl::~thread_impl()
    {
    }

    int thread_impl::run()
    {
        if (threadDesc) { /* Already running */
            return -1;
        }

        /* We assume here that sizeof(unsigned int) == sizeof(void*) */
        return pthread_create(
            &this->threadDesc,
            NULL,
            (void* (*)(void*))this->threadFn,
            this->threadArg);
    }

    int thread_impl::join()
    {
        return pthread_join(this->threadDesc, NULL);
    }

    int thread_impl::detach()
    {
        return pthread_detach(this->threadDesc);
    }

    int thread_impl::getCurrentThreadId()
    {
        return pthread_self();
    }
}
}
