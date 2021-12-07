/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_IMPL_OBJECT_FACTORIES_IMPL_H
#define BASYX_SHARED_OBJECT_IMPL_OBJECT_FACTORIES_IMPL_H

#include <BaSyx/util/printer.h>
#include <BaSyx/util/util.h>
#include <BaSyx/util/make_function.h>

#include <BaSyx/shared/object/obj_function.h>
#include <BaSyx/shared/object/obj_holder.h>
#include <BaSyx/shared/object/obj_ref_holder.h>

template <typename T>
basyx::object::object(const T& t)
: content{ std::make_shared<basyx::detail::objHolder<typename std::remove_cv<typename std::decay<const T>::type>::type>>(t) } {};


template<typename T>
basyx::object basyx::object::make_object_ref(T* t)
{
	basyx::object obj;
	obj.content = std::make_shared<detail::objRefHolder<
		typename std::remove_cv<typename std::decay<const T>::type>::type>>(t);
	return obj;
};

template<typename T, typename... Args>
basyx::object basyx::object::make_list(Args && ... args)
{
	return basyx::object{ object::list_t<T>(std::forward<Args>(args)...) };
};

template<typename T>
basyx::object basyx::object::make_list(std::initializer_list<T> l)
{
	return basyx::object{ object::list_t<T>(std::forward<std::initializer_list<T>>(l)) };
};

template<typename... Args>
basyx::object basyx::object::make_object_list(Args && ... args)
{
	return basyx::object{ object::list_t<basyx::object>(std::forward<Args>(args)...) };
};

template<typename... Args>
basyx::object basyx::object::make_map(Args && ... args)
{
	return basyx::object{ object::object_map_t(std::forward<Args>(args)...) };
};

template<typename... Args>
basyx::object basyx::object::make_function(Args && ... args)
{
	return basyx::detail::functionWrapper::wrap_func(util::make_function(std::forward<Args>(args)...));
};

#endif /* BASYX_SHARED_OBJECT_IMPL_OBJECT_FACTORIES_IMPL_H */
