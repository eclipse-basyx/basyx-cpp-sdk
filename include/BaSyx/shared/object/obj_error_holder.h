/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJ_ERROR_HOLDER_H
#define BASYX_SHARED_OBJECT_OBJ_ERROR_HOLDER_H

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

    // ErrorHolder:
    // PlaceHolder storing an error value with an error message
    class objErrorHolder : public objPlaceHolder {
    public:
        using json_t = nlohmann::json;
	public:
		std::string message;
		basyx::object::error error;
    public: // structors
		objErrorHolder(basyx::object::error error) : error(error) {};
		objErrorHolder(basyx::object::error error, const std::string & message) : error(error), message(message) {};

		virtual ~objErrorHolder() = default;
    public:
        virtual const std::type_info& type() const noexcept override
        {
            return typeid(basyx::object::error);
        };

        virtual bool compare(objPlaceHolder * rhs) const override {
			return false;
        }

		virtual objPlaceHolder::HolderType get_holder_type() const noexcept override
		{
			return objPlaceHolder::HolderType::Error;
		};

		virtual void * get_address() const noexcept override
		{
			return (void*)this;
		};

		virtual basyx::type::objectType object_type() const override
		{
			return basyx::type::objectType::Error;
		};
				
		virtual basyx::type::valueType value_type() const override
		{
			return basyx::type::valueType::Null;
		};

		virtual void to_json(json_t& json) const override
		{
			json = json_t{ "error", this->message };
		};
	private:
		objErrorHolder & operator=(const objErrorHolder&) = delete;
    };
}
}

#endif /* BASYX_SHARED_OBJECT_OBJ_ERROR_HOLDER_H */
