/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_PROPERTY_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_PROPERTY_H

#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>

#include <BaSyx/aas/api_v2/submodelelement/property/IProperty.h>
#include <BaSyx/aas/simple/submodelelement/SubmodelElement.h>


namespace basyx {
namespace aas {
namespace simple {

template<typename T>
class Property
  : public SubmodelElement
  , public virtual api::IProperty
{
private:
	std::string valueType;
	T value;
	Reference valueId;
public:
	Property(const std::string & idShort)
		: SubmodelElement(idShort)
	{
	};

	virtual ~Property() = default;

	void setValue(const T & t)
	{
		this->value = t;
	}

	const T & getValue() const
	{
		return this->value;
	}

	virtual const std::string & getValueType() const override
	{
		return this->valueType;
	}

	virtual void setValueType(const std::string & valueType) override
	{
		this->valueType = valueType;
	}

	virtual basyx::object getObject() override
	{
		return basyx::object(value);
	}

	virtual void setObject(basyx::object & object) override
	{
		if (object.InstanceOf<T>())
			this->value = object.template Get<T&>();
	}

	virtual const Reference * const getValueId() const override
	{
		return &this->valueId;
	}

	virtual void setValueId(const api::IReference & valueId) override
	{
		this->valueId = valueId;
	}

  virtual KeyElements getKeyElementType() const override { return KeyElements::Property; };
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_PROPERTY_H */
