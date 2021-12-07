/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_QUALIFIER_HASDATASPECIFICATION_H
#define BASYX_SUBMODEL_SIMPLE_QUALIFIER_HASDATASPECIFICATION_H

#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/simple/reference/Reference.h>


namespace basyx {
namespace aas {
namespace simple {

class HasDataSpecification
  : public virtual api::IHasDataSpecification
{
private:
	std::vector<Reference> dataSpecification;
public:
	HasDataSpecification();

	virtual ~HasDataSpecification() = default;
public:
	void addDataSpecification(const Reference & reference) override;
	const std::vector<Reference> getDataSpecificationReference() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_QUALIFIER_HASDATASPECIFICATION_H */
