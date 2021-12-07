/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATIONIEC61360_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATIONIEC61360_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationIEC61360.h>
#include <BaSyx/aas/simple/common/LangStringSet.h>
#include <BaSyx/aas/simple/reference/Reference.h>

namespace basyx {
namespace aas {
namespace simple {

class DataSpecificationIEC61360 : public api::IDataSpecificationIEC61360
{
private:
	LangStringSet preferredName;
	LangStringSet shortName;
	LangStringSet definition;

	std::string unit;
	Reference unitId;
	std::string sourceOfDefinition;
	DataTypeIEC61360 dataType;
	std::string valueFormat;
	Reference valueId;
	LevelType levelType;
public:
	DataSpecificationIEC61360(const LangStringSet & preferredName);
	DataSpecificationIEC61360(const std::string & langCode, const std::string & preferredName);
	~DataSpecificationIEC61360() = default;
public:
	virtual LangStringSet & PreferredName() override;
	virtual LangStringSet & ShortName() override;
	virtual LangStringSet & Definition() override;

	virtual std::string * const getUnit() override;
	virtual Reference * const getUnitId() override;
	virtual std::string * const getSourceOfDefinition() override;
	virtual DataTypeIEC61360 getDataType() const override;
	virtual std::string * const getValueFormat() override;
	virtual Reference * const getValueId() override;
	virtual LevelType getLevelType() const override;

	virtual void setUnit(const std::string & unit) override;
	virtual void setSourceOfDefinition(const std::string & sourceOfDefinition) override;
	virtual void setDataType(DataTypeIEC61360 dataType) override;
	virtual void setValueFormat(const std::string & valueFormat) override;
	virtual void setLevelType(LevelType levelType) override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATIONIEC61360_H */
