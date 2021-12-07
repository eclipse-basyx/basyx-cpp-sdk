/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJ_HOLDER_H
#define BASYX_SHARED_OBJECT_OBJ_HOLDER_H

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

    // Holder:
    // The actual class holding the object, is derived from PlaceHolder and parametrized through template parameter T
    template <typename T>
    class objHolder : public objPlaceHolder {
    public:
        using json_t = nlohmann::json;
	public:
		// Actual stored value
		T stored;
    public: // structors
		objHolder(const T& t)
            : stored(t) {};

		objHolder(T&& t)
            : stored(std::move(t)) {};

	public:
        virtual const std::type_info& type() const noexcept override
        {
            return typeid(T);
        };

		virtual objPlaceHolder::HolderType get_holder_type() const noexcept override
		{
			return objPlaceHolder::HolderType::Owning;
		};

        virtual bool compare(objPlaceHolder * rhs) const override {
        	if (rhs->type() != this->type())
        		return false;

        	return this->stored == static_cast<objHolder<T>*>(rhs)->stored;
        }

        virtual void to_json(json_t& json) const override
        {
            json = basyx::serialization::json::serialize(stored);
        };

		virtual void * get_address() const noexcept override
		{
			return (void*)&this->stored;
		};

		virtual basyx::type::objectType object_type() const override
		{
			return basyx::type::basyx_type<T>::object_type;
		};
				
		virtual basyx::type::valueType value_type() const override
		{
			return basyx::type::basyx_type<T>::value_type;
		};

	private:
        objHolder& operator=(const objHolder&) = delete;
    };
}
}

#endif /* BASYX_SHARED_OBJECT_OBJ_HOLDER_H */
