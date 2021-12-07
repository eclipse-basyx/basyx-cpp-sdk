/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/provider/VABModelProvider.h>


using namespace basyx::vab::provider;

VABModelProvider::VABModelProvider(const basyx::object& any) 
	: elements(any) 
{
};

basyx::object VABModelProvider::getParentElement(const std::string& path)
{
	core::VABPath vabPath{ path };

	auto currentElement = elements;

	// ignore the leaf element, only return the leaf's parent element
	const auto & pathElements = vabPath.getElements();
	for(std::size_t i=0; i < pathElements.size()-1; ++i)
	{
		if (currentElement.IsNull())
			return basyx::object::make_null();

		currentElement = currentElement.getProperty(pathElements[i]); //  handler.GetElementProperty(currentElement, pathElements[i]);
	}

	return currentElement;
};

basyx::object VABModelProvider::getTargetElement(const std::string& path)
{
	core::VABPath vabPath{ path };
	if (vabPath.isEmpty()) {
		return elements;
	}
	else
	{
		auto parentElement = getParentElement(path);
		auto operationName = vabPath.getLastElement();
		if (!parentElement.IsNull() && !operationName.empty()) {
			//return handler.GetElementProperty(parentElement, operationName);
			return parentElement.getProperty(operationName);
		}
		else if (parentElement.IsError())
		{
			return parentElement;
		};
	};

	return basyx::object::make_null();
};

basyx::object VABModelProvider::getModelPropertyValue(const std::string& path)
{
	core::VABPath vabPath{ path };
	auto & lastPathElement = vabPath.getLastElement();

	if (vabPath.isEmpty()) {
		//return handler.PostProcessObject(elements);
		return elements;
	}

	auto element = getTargetElement(path);
//			return handler.PostProcessObject(element);
	return element;
}

basyx::object::error VABModelProvider::setModelPropertyValue(const std::string& path, const basyx::object newValue)
{
	core::VABPath vabPath{ path };

	// Check empty paths
	if (vabPath.isEmpty()) {
		// If path is empty, replace parent element, but only if it does already exist
		if (!elements.IsNull()) {
			elements = newValue;
			return basyx::object::error::None;
		};
		
		// Otherwise return error
		return basyx::object::error::ObjectAlreadyExists;
	}

	auto parentElement = this->getParentElement(path);
	auto & propertyName = vabPath.getLastElement();

	// Only write values, that already exist
	auto thisElement = parentElement.getProperty(propertyName);

	if (!parentElement.IsNull() && !thisElement.IsError() ) {
		parentElement.insertKey(propertyName, newValue, true);
		return basyx::object::error::None;
	}

	return basyx::object::error::PropertyNotFound;
};

basyx::object::error VABModelProvider::createValue(const std::string& path, const basyx::object newValue)
{
	core::VABPath vabPath{ path };

	// Check empty paths
	if (vabPath.isEmpty()) {
		// The complete model should be replaced if it does not exist
		if (elements.IsNull()) {
			elements = newValue;
			return basyx::object::error::None;
		}
		return basyx::object::error::ObjectAlreadyExists;
	}

	// Find parent & name of new element
	auto parentElement = this->getParentElement(path);
	auto & propertyName = vabPath.getLastElement();

	// Parent not found, return error
	if (parentElement.IsNull()) {
		log.warn("Could not create element, parent element does not exist for path '{}'", path);
		return basyx::object::error::PropertyNotFound;
	};

	if(parentElement.GetObjectType() == basyx::type::objectType::Map)
	{
		auto childElement = parentElement.getProperty(propertyName);
		// Only create new, never replace existing elements
		if (childElement.IsNull()) {
			parentElement.insertKey(propertyName, newValue);
			return basyx::object::error::None;
		}
		else 
		{
			// If list, insert value
			if (childElement.GetObjectType() == basyx::type::objectType::List)
			{
				childElement.insert(newValue);
				return basyx::object::error::None;
			}
			else
			{
				return basyx::object::error::ObjectAlreadyExists;
			};
		}
	};

	return basyx::object::error::MalformedRequest;
};

basyx::object::error VABModelProvider::deleteValue(const std::string& path, basyx::object deletedValue)
{
	core::VABPath vabPath{ path };

	if (vabPath.isEmpty())
		return basyx::object::error::MalformedRequest;

	// Find parent & name of element
	auto parentElement = this->getParentElement(path);
	auto & propertyName = vabPath.getLastElement();

	if (!parentElement.IsNull()) {
		//auto & childElement = handler.GetElementProperty(parentElement, propertyName);
		auto childElement = parentElement.getProperty(propertyName);


		if (!childElement.IsNull()) {
			//handler.DeleteValue(childElement, deletedValue);
			if (!childElement.remove(deletedValue))
				return basyx::object::error::MalformedRequest;
			return basyx::object::error::None;
		}
	}

	return basyx::object::error::PropertyNotFound;
};

basyx::object::error VABModelProvider::deleteValue(const std::string& path)
{
	core::VABPath vabPath{ path };

	// Find parent & name of element
	auto parentElement = this->getParentElement(path);
	auto & propertyName = vabPath.getLastElement();

	if (!parentElement.IsNull()) {
		//handler.DeleteProperty(parentElement, propertyName);
		if(parentElement.removeProperty(propertyName))
			return basyx::object::error::None;

		return basyx::object::error::PropertyNotFound;
	}

	return basyx::object::error::PropertyNotFound;
};

basyx::object VABModelProvider::invokeOperation(const std::string& path, basyx::object parameters)
{
	log.trace("invokeOperationImpl called");
	log.trace("    path: \"{}\"", path);
	log.trace("    parameters: <not impl>");

	auto element = this->getModelPropertyValue(path);

	if (element.IsNull() || element.IsError()) {
		log.error("Function not found!");
		log.trace("Returning basyx::object::null");

		return basyx::object::make_error(basyx::object::error::PropertyNotFound, "method not found");
	}

	if (!element.IsInvokable()) {
		log.error("Found object is not invokable!");
		log.trace("Returning basyx::object::null");

		return basyx::object::make_error(basyx::object::error::ProviderException, "method not invokable");
	};

	log.trace("Function found. Invoking...");

	return element.invoke(parameters);
};