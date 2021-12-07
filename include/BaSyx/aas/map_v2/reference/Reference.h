/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_REFERENCE_REFERENCE_H
#define BASYX_SUBMODEL_MAP_V2_REFERENCE_REFERENCE_H

#include <BaSyx/aas/api_v2/reference/IReference.h>
#include <BaSyx/aas/simple/reference/Key.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

class Reference : 
	public api::IReference,
	public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char IdType[] = "idType";
    static constexpr char Type[] = "type";
    static constexpr char Value[] = "value";
    static constexpr char Local[] = "local";
    static constexpr char Keys[] = "keys";
  };
public:
	Reference();
public:
	using vab::ElementMap::ElementMap;

	Reference(const api::IReference & other);
	Reference(const Reference & other) = default;
	Reference(Reference && other) noexcept = default;
  Reference(basyx::object & object);

  static Reference from_object(basyx::object &);

	Reference & operator=(const api::IReference & other);
	Reference & operator=(const Reference & other) = default;
	Reference & operator=(Reference && other) noexcept = default;

	Reference(const simple::Key & key);
	Reference(const std::vector<simple::Key> & keys);

	virtual ~Reference() = default;
public:
	std::vector<simple::Key> getKeys() const override;
	void addKey(const simple::Key & key) override;

	virtual bool empty() const override;


  bool operator!=(const Reference & other) const;
  inline bool operator==(const Reference & other) const { return !(*this != other); };

  bool operator!=(const api::IReference & other) const;
  inline bool operator==(const api::IReference & other) const { return !(*this != other); };
public:
//	static Reference FromIdentifiable(const std::string & keyElementType, bool local, const IIdentifiable & identifiable);

private:
  static simple::Key keyMap_to_key(basyx::object &keyMap);
  static std::vector<simple::Key> keyMapList_to_keyList(basyx::object::object_list_t &keyMapList);
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_REFERENCE_REFERENCE_H */
