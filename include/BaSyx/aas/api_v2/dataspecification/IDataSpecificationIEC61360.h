/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONIEC61360_H
#define BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONIEC61360_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationContent.h>
#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/api_v2/qualifier/IReferable.h>
#include <BaSyx/aas/api_v2/reference/IReference.h>
#include <BaSyx/aas/enumerations/DataTypeIEC61360.h>
#include <BaSyx/aas/enumerations/LevelType.h>


namespace basyx {
namespace aas {

namespace api {

class IDataSpecificationIEC61360
    : public IDataSpecificationContent
{
public:
	virtual ~IDataSpecificationIEC61360() = 0;

	virtual ILangStringSet & PreferredName() = 0;
	virtual ILangStringSet & ShortName() = 0;
	virtual ILangStringSet & Definition() = 0;

	virtual std::string * const getUnit() = 0;
	virtual IReference * const getUnitId() = 0;
	virtual std::string * const getSourceOfDefinition() = 0;
	virtual std::string * const getSymbol() = 0;
	virtual DataTypeIEC61360 getDataType() const = 0;
	virtual std::string * const getValueFormat() = 0;
/* TODO
	virtual MISSINGTYPE const getValueList() = 0;
  virtual MISSINGTYPE const getValueDataType() = 0;
	*/
  virtual IReference * const getValueId() = 0;
	virtual LevelType getLevelType() const = 0;

	virtual void setUnit(const std::string & unit) = 0;
	virtual void setSourceOfDefinition(const std::string & sourceOfDefinition) = 0;
	virtual void setDataType(DataTypeIEC61360 dataType) = 0;
	virtual void setValueFormat(const std::string & valueFormat) = 0;
	virtual void setLevelType(LevelType levelType) = 0;
};

inline IDataSpecificationIEC61360::~IDataSpecificationIEC61360() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONIEC61360_H */
