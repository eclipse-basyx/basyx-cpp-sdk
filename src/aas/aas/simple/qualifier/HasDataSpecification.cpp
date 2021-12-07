/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/qualifier/HasDataSpecification.h>

#include <BaSyx/aas/simple/reference/Reference.h>

namespace basyx {
namespace aas {
namespace simple {

HasDataSpecification::HasDataSpecification()
{
}

void HasDataSpecification::addDataSpecification(const Reference & reference)
{
	this->dataSpecification.emplace_back(reference);
};

const std::vector<Reference> HasDataSpecification::getDataSpecificationReference() const
{
	return this->dataSpecification;
}

}
}
}
