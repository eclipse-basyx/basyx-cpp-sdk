/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJ_REF_HOLDER_H
#define BASYX_SHARED_OBJECT_OBJ_REF_HOLDER_H

#include <memory>
#include <string>
#include <typeinfo>

#include <nlohmann/json.hpp>

#include <BaSyx/util/printer.h>
#include <BaSyx/util/util.h>

#include <BaSyx/shared/object/obj_placeholder.h>
#include <BaSyx/shared/serialization/json.h>

namespace basyx {
namespace detail {

    // RefHolder:
    // PlaceHolder storing an observing pointer to an object, instead of owning it, parametrized through template parameter T
    template <typename T>
    class objRefHolder : public objPlaceHolder {
    public:
        using json_t = nlohmann::json;
	public:
		T * const observed;
    public: // structors
		objRefHolder(const T & t)
            : observed(&t) {};

		objRefHolder(T* t)
			: observed(t) {};
    public:
        virtual const std::type_info& type() const noexcept override
        {
            return typeid(T);
        };

        virtual bool compare(objPlaceHolder * rhs) const override {
        	if (rhs->type() != this->type())
        		return false;

			return false;
//        	return *this->observed == static_cast<objHolder<T>*>(rhs)->stored;
        }

		virtual objPlaceHolder::HolderType get_holder_type() const noexcept override
		{
			return objPlaceHolder::HolderType::Observing;
		};

		virtual void * get_address() const noexcept override
		{
			return (void*)this->observed;
		};

		virtual basyx::type::objectType object_type() const override
		{
			return basyx::type::basyx_type<T>::object_type;
		};
				
		virtual basyx::type::valueType value_type() const override
		{
			return basyx::type::basyx_type<T>::value_type;
		};

		virtual void to_json(json_t& json) const override
		{
			json = basyx::serialization::json::serialize(*observed);
		};
	private:
		objRefHolder& operator=(const objRefHolder&) = delete;
    };
}
}

#endif /* BASYX_SHARED_OBJECT_OBJ_REF_HOLDER_H */
