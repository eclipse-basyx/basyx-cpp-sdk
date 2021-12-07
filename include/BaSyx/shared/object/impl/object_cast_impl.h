/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_IMPL_OBJECT_CAST_IMPL_H
#define BASYX_SHARED_OBJECT_IMPL_OBJECT_CAST_IMPL_H

#include <BaSyx/shared/object/object_header.h>
#include <BaSyx/shared/object/obj_holder.h>
#include <BaSyx/shared/object/obj_ref_holder.h>
#include <BaSyx/shared/object/bad_object_cast.h>


// object_cast:
// Cast a basyx::object object to the desired type
// If the cast itself is not allowed on the held object, basyx::bad_object_cast exception will be thrown
template <typename T>
T basyx::object::object_cast(object& operand)
{
	using non_ref_t = typename std::remove_reference<T>::type;

	non_ref_t* result = object_cast<non_ref_t>(&operand);

	if (result == nullptr)
		throw basyx::bad_object_cast(operand.type(), typeid(T));

	// Use reference to avoid temporary object creation
	using ref_t = typename std::conditional<std::is_reference<T>::value, T, T&>::type;

	return static_cast<ref_t>(*result);
}

template <typename T>
T* basyx::object::object_cast_ptr(object * operand)
{
	auto address = operand->content->get_address();

	auto ptr = static_cast<T*>(address);

	return ptr;
}

template <typename T>
T* basyx::object::object_cast(object* operand) noexcept
{
	if (operand == nullptr)
		return nullptr;

	auto holder_type = operand->content->get_holder_type();

	if (operand->type() == typeid(T))
	{
		if (holder_type == PlaceHolder::HolderType::Observing)
		{
			return static_cast<basyx::detail::objRefHolder<typename std::remove_cv<T>::type>*>(operand->content.get())->observed;
		}
		else if (holder_type == PlaceHolder::HolderType::Owning)
		{
			return &static_cast<basyx::detail::objHolder<typename std::remove_cv<T>::type>*>(operand->content.get())->stored;
		};
	}

	// if nothing works, return nullptr
	return nullptr;
}

template <typename T>
inline const T* basyx::object::object_cast(const object* operand)
{
	return object_cast<T>(const_cast<object*>(operand));
}

#endif /* BASYX_SHARED_OBJECT_IMPL_OBJECT_CAST_IMPL_H */
