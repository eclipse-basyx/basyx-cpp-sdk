/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_IMPL_OBJECT_META_IMPL_H
#define BASYX_SHARED_OBJECT_IMPL_OBJECT_META_IMPL_H

template <typename T>
bool basyx::object::operator!=(const T& rhs) const
{
	return !this->operator==(rhs);
}

template <typename T>
bool basyx::object::operator==(const T& rhs) const
{
	if (this->type() == typeid(T)) {
		return const_cast<basyx::object*>(this)->Get<T&>() == rhs;
	}
	return false;
}


#endif /* BASYX_SHARED_OBJECT_IMPL_OBJECT_META_IMPL_H */
