/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>

#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

constexpr char HasDataSpecification::Path::DataSpecification[];

HasDataSpecification::HasDataSpecification()
	: vab::ElementMap()
	, dataSpecification()
{
	this->map.insertKey(Path::DataSpecification, this->dataSpecification);
}


HasDataSpecification::HasDataSpecification(basyx::object obj)
  : ElementMap()
  , dataSpecification()
{
  this->map.insertKey(Path::DataSpecification, this->dataSpecification);

  auto dataSpec_objects = obj.getProperty(Path::DataSpecification).Get<basyx::object::object_list_t>();
  for (basyx::object dataSpec_obj : dataSpec_objects)
  {
    auto mapRef = map::Reference::from_object( dataSpec_obj);
    this->addDataSpecification(mapRef);
  }
}

void HasDataSpecification::addDataSpecification(const simple::Reference & reference)
{
	map::Reference ref { reference.getKeys() };
	this->dataSpecification.emplace_back(ref.getMap());
  this->map.insertKey(Path::DataSpecification, this->dataSpecification);
}

const std::vector<simple::Reference> HasDataSpecification::getDataSpecificationReference() const
{
	std::vector<simple::Reference> dataSpecs;

	for (auto & refObj : dataSpecification) {
		map::Reference mapRef{ refObj };
		dataSpecs.emplace_back(mapRef.getKeys());
	}

	return dataSpecs;
}
