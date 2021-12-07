/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_QUALIFIER_HASDATASPECIFICATION_H
#define BASYX_SUBMODEL_MAP_V2_QUALIFIER_HASDATASPECIFICATION_H

#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

class HasDataSpecification : 
	public virtual api::IHasDataSpecification,
	public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char DataSpecification[] = "dataSpecification";
  };

private:
	basyx::object::object_list_t dataSpecification;

public:
	HasDataSpecification();
	HasDataSpecification(basyx::object);

	virtual ~HasDataSpecification() = default;
public:
	virtual void addDataSpecification(const simple::Reference & reference) override;
	virtual const std::vector<simple::Reference> getDataSpecificationReference() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_QUALIFIER_HASDATASPECIFICATION_H */
