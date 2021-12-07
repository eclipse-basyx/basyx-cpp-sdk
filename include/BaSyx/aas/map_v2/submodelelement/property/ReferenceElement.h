/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_REFERENCEELEMENT_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_REFERENCEELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/property/IReferenceElement.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>

namespace basyx {
namespace aas {
namespace map {

class ReferenceElement
  : public virtual api::IReferenceElement
  , public DataElement
  , public ModelType<ModelTypes::ReferenceElement>
{
public:
  struct Path {
    static constexpr char Value[] = "value";
    static constexpr char Kind[] = "kind";
  };
private:
    std::unique_ptr<Reference> value;
public:
    ReferenceElement(const std::string& idShort, ModelingKind kind = ModelingKind::Instance);
    ReferenceElement(basyx::object);

    virtual ~ReferenceElement() = default;

    virtual const api::IReference* const getValue() const override;
    virtual void setValue(const api::IReference& value) override;

    virtual KeyElements getKeyElementType() const override { return KeyElements::ReferenceElement; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_REFERENCEELEMENT_H */
