/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/dataspecification/DataSpecification.h>
#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map{

using namespace basyx::aas::api;

constexpr char DataSpecification::Path::DataSpecificationContent[];

DataSpecification::DataSpecification(const std::string & idShort, const simple::Identifier & identifier, std::unique_ptr<DataSpecificationContent> content)
  : Identifiable(idShort, identifier)
  , vab::ElementMap()
{
  this->setContent(std::move(content));
}

DataSpecification::DataSpecification(const std::string &idShort, const simple::Identifier &identifier)
    : Identifiable(idShort, identifier)
    , vab::ElementMap{}
{}

void DataSpecification::setContent(std::unique_ptr<DataSpecificationContent> dataSpecificationContent)
{
  this->content = std::move(dataSpecificationContent);
  auto element_map = dynamic_cast<vab::ElementMap*>(this->content.get());
  this->map.insertKey(Path::DataSpecificationContent, element_map->getMap());
}

api::IDataSpecificationContent& DataSpecification::getContent()
{
  return *this->content;
}

}
}
}
