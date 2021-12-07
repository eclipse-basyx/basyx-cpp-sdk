/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IANNOTATEDRELATIONSHIPELEMENT_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IANNOTATEDRELATIONSHIPELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/IDataElement.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>

namespace basyx {
namespace aas {
namespace api {

class IAnnotatedRelationshipElement : public IDataElement
{
public:
  virtual ~IAnnotatedRelationshipElement() = 0;

  virtual const IElementContainer<IDataElement> & getAnnotation() const = 0;

  virtual KeyElements getKeyElementType() const override { return KeyElements::AnnotatedRelationshipElement; };
};

inline IAnnotatedRelationshipElement::~IAnnotatedRelationshipElement() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IANNOTATEDRELATIONSHIPELEMENT_H */
