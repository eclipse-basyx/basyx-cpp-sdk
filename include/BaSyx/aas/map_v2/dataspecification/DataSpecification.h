/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATION_H
#define BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATION_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecification.h>
#include <BaSyx/aas/map_v2/dataspecification/DataSpecificationContent.h>
#include <BaSyx/aas/map_v2/qualifier/Identifiable.h>
#include <BaSyx/aas/simple/dataspecification/DataSpecification.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

class DataSpecification :
    public api::IDataSpecification,
    public virtual Identifiable,
    public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char DataSpecificationContent[] = "dataSpecificationContent";
  };

private:
  std::unique_ptr<DataSpecificationContent> content;
public:
  DataSpecification(const std::string & idShort, const simple::Identifier & identifier, std::unique_ptr<DataSpecificationContent> content);
  DataSpecification(const std::string & idShort, const simple::Identifier & identifier);

  api::IDataSpecificationContent & getContent() override;

  void setContent(std::unique_ptr<DataSpecificationContent> content);
  virtual KeyElements getKeyElementType() const override { return KeyElements::Unknown; };
};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATION_H */
