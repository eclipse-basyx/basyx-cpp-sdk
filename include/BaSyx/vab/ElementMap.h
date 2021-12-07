/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_AAS_METAMODEL_ELEMENTMAP_H_
#define BASYX_AAS_METAMODEL_ELEMENTMAP_H_

#include <BaSyx/shared/object.h>

namespace basyx {
namespace vab {


class ElementMap
{
protected:
	mutable basyx::object map;

protected:

public:
	ElementMap();
	ElementMap(basyx::object object);
  ElementMap(const ElementMap & other);
	virtual ~ElementMap() = default;
	
	void insertMapElement(const std::string & key, const ElementMap & element);

	basyx::object getMap() const;

public:
	template<typename AbstractType, typename SpecificType>
	static basyx::specificCollection_t<AbstractType> make_specific_collection(basyx::object::object_list_t & obj_list)
	{
		basyx::specificCollection_t<AbstractType> list;

		for (auto & obj : obj_list)
			list.emplace_back(std::make_shared<SpecificType>(obj));

		return list;
	};

	template<typename AbstractType, typename SpecificType>
	static basyx::object make_object_list(const basyx::specificCollection_t<AbstractType> & abst_list)
	{
		auto list = basyx::object::make_list<basyx::object>();

		for (auto & abstract : abst_list)
			list.insert(SpecificType{ *abstract }.getMap());

		return list;
	};
};

}
}

#endif
