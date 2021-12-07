/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/constraint/Formula.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>


using namespace basyx::aas;
using namespace basyx::aas::map;

constexpr char Formula::Path::Dependencies[];

Formula::Formula()
  : ElementMap{}
{
	this->map.insertKey(Path::Dependencies, basyx::object::make_object_list());
}

Formula::Formula(basyx::object obj)
  : Formula()
{
  auto & dependencies = obj.getProperty(Path::Dependencies).Get<object::object_list_t&>();
  auto & objectList = this->map.getProperty(Path::Dependencies).Get<basyx::object::object_list_t&>();

  for (const auto & dependency : dependencies)
  {
    map::Reference ref{ dependency };

    objectList.emplace_back(ref.getMap());
  }
}

Formula::Formula(const std::vector<simple::Reference> & dependencies)
	: Formula()
{
	auto & objectList = this->map.getProperty(Path::Dependencies).Get<basyx::object::object_list_t&>();

	for (const auto & dependency : dependencies)
	{
		map::Reference ref{ dependency };

		objectList.emplace_back(ref.getMap());
	}
}

Formula::Formula(const api::IFormula & other)
	: Formula(other.getDependencies())
{}

std::vector<simple::Reference> Formula::getDependencies() const
{
	std::vector<simple::Reference> dependencies;

	auto & objectList = this->map.getProperty(Path::Dependencies).Get<basyx::object::object_list_t&>();

	for (const auto & obj : objectList)
	{
		map::Reference ref{ obj };

		dependencies.emplace_back(ref);
	};

	return dependencies;
}

void Formula::addDependency(const api::IReference & reference)
{
	map::Reference ref{ reference };

	auto & objectList = this->map.getProperty(Path::Dependencies).Get<basyx::object::object_list_t&>();
	objectList.emplace_back(ref.getMap());
}

