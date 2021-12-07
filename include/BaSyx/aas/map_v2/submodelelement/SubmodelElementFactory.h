/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_SUBMODELELEMENTFACTORY_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_SUBMODELELEMENTFACTORY_H

#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

class SubmodelElementFactory
{
public:
  struct Path {
    static constexpr char Value[] = "value";
  };
private:
  static std::unique_ptr<map::DataElement> CreateProperty(const vab::ElementMap & elementMap);
  static std::unique_ptr<map::DataElement> CreateRange(const vab::ElementMap & elementMap);
public:
	static std::unique_ptr<map::SubmodelElement> Create(const vab::ElementMap & elementMap);
  static std::unique_ptr<map::DataElement> CreateDataElement(const vab::ElementMap & elementMap);
};

}
}
}

#endif