/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/backend/connector/native/frame/EntityWrapper.h>

using basyx::vab::EntityWrapper;


namespace {
	std::string prepareErrorCode(basyx::object::error errorCode)
	{
		std::string error;
		switch (errorCode)
		{
		case basyx::object::error::PropertyNotFound:
			error = "404";
			break;
		case basyx::object::error::ObjectAlreadyExists:
			error = "422";
			break;
		case basyx::object::error::MalformedRequest:
			error = "400";
			break;
		default:
			error = "500";
			break;
		};
		return error;
	};

	std::string prepareErrorMessage(basyx::object::error errorCode, const std::string & message)
	{
		return prepareErrorCode(errorCode) + ": " + message;
	};
}

basyx::object build_exception(const std::string & code, const std::string & message)
{
	basyx::object::error error = basyx::object::error::ProviderException;

	if (code == "404")
	{
		error = basyx::object::error::PropertyNotFound;
	}
	else if (code == "422")
	{
		error = basyx::object::error::ObjectAlreadyExists;
	}
	else if (code == "400")
	{
		error = basyx::object::error::MalformedRequest;
	}
	else if (code == "500")
	{
		error = basyx::object::error::ProviderException;
	};

	return basyx::object::make_error(error, message);
};

basyx::json_t EntityWrapper::build_from_error(basyx::object::error error, const std::string & message)
{
	json_t msg;
	msg["messageType"] = "Information";
	msg["text"] = prepareErrorMessage(error, message);
	msg["code"] = prepareErrorCode(error);

	basyx::json_t j_obj;
	j_obj["success"] = false;
	j_obj["messages"] = json_t::array({ msg });
	return j_obj;
};

basyx::json_t EntityWrapper::build_from_object(const basyx::object & object)
{
	if (object.IsError())
	{
		return build_from_error(object.getError(), object.getErrorMessage());
	}
	else
	{
		return basyx::serialization::json::serialize(object);
	}
};


basyx::object EntityWrapper::from_json(const basyx::json_t & json)
{
	bool exception = (json.contains("success") && !json["success"]);

	// everyhing okay, deserialize entity
	if (!exception)
	{
		return basyx::serialization::json::deserialize(json);
	}
	// something went wrong, check for exception
	else if (json.contains("messages"))
	{
		auto & msg = json["messages"][0];

		auto code = msg["code"];
		auto text = msg["text"];

		return build_exception(code, text);
	}
	// error and no exception; create one
	else
	{
		return basyx::object::make_error(basyx::object::error::MalformedRequest);
	};
};