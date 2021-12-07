/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTFACTORY_H
#define BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTFACTORY_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>

namespace basyx {
namespace aas {
namespace map {

template<typename IElementType>
class ElementFactory
{
public:
	inline static std::unique_ptr<IElementType> Create(const vab::ElementMap & elementMap) {
		return nullptr;
	};
};

template<>
class ElementFactory<api::ISubmodelElement>
{
public:
	inline static std::unique_ptr<api::ISubmodelElement> Create(const vab::ElementMap & elementMap) {
		return SubmodelElementFactory::Create(elementMap);
	};
};

}
}
}


#endif /* BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTFACTORY_H */
