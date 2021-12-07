/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/reference/Reference.h>

#include <BaSyx/aas/enumerations/KeyType.h>
#include <BaSyx/aas/enumerations/KeyElements.h>

#include <vector>

using namespace basyx::aas;
using namespace basyx::aas::map;

constexpr char Reference::Path::IdType[];
constexpr char Reference::Path::Type[];
constexpr char Reference::Path::Value[];
constexpr char Reference::Path::Local[];
constexpr char Reference::Path::Keys[];

Reference::Reference() 
	: vab::ElementMap{}
{
	this->map.insertKey(Path::Keys, basyx::object::make_object_list());
}

Reference::Reference(const simple::Key & key)
	: Reference{}
{
	this->addKey(key);
};

Reference::Reference(const std::vector<simple::Key> & keys)
	: Reference{}
{
	for (const auto & key : keys)
		this->addKey(key);
};

Reference::Reference(const IReference & other)
	: Reference{other.getKeys()}
{}

Reference::Reference(basyx::object &object)
  : Reference(keyMapList_to_keyList(object.getProperty(Path::Keys).Get<object::object_list_t&>()))
{}

Reference Reference::from_object(basyx::object & object)
{
  return Reference(keyMapList_to_keyList(object.getProperty(Path::Keys).Get<object::object_list_t&>()));
}

std::vector<simple::Key> Reference::getKeys() const
{
  return this->keyMapList_to_keyList(this->map.getProperty(Path::Keys).Get<basyx::object::object_list_t &>());
}

void Reference::addKey(const simple::Key & key)
{
	basyx::object keyMap = basyx::object::make_map();
	keyMap.insertKey(Path::IdType, KeyType_::to_string(key.getIdType()));
	keyMap.insertKey(Path::Type, KeyElements_::to_string(key.getType()));
	keyMap.insertKey(Path::Value, key.getValue());
	keyMap.insertKey(Path::Local, key.isLocal());
	this->map.getProperty(Path::Keys).insert(keyMap);
}

Reference & Reference::operator=(const api::IReference & other)
{
	this->map.insertKey(Path::Keys, basyx::object::make_object_list());

	for (const auto & key : other.getKeys())
		this->addKey(key);

	return *this;
}


bool Reference::empty() const
{
	return this->map.getProperty(Path::Keys).empty();
}

simple::Key Reference::keyMap_to_key(basyx::object &keyMap)
{
  return simple::Key
  (
    KeyElements_::from_string(keyMap.getProperty(Path::Type).Get<std::string&>()),
    keyMap.getProperty(Path::Local).Get<bool>(),
    KeyType_::from_string(keyMap.getProperty(Path::IdType).Get<std::string&>()),
    keyMap.getProperty(Path::Value).Get<std::string&>()
  );
}

std::vector<simple::Key> Reference::keyMapList_to_keyList(basyx::object::object_list_t &keyMapList)
{
  std::vector<simple::Key> keys;

  for (auto & keyMap : keyMapList)
  {
    keys.emplace_back(keyMap_to_key(keyMap));
  };

  return keys;
}

bool Reference::operator!=(const Reference & other) const
{
  return this->getKeys() != other.getKeys();
};

bool Reference::operator!=(const api::IReference & other) const
{
  return this->getKeys() != other.getKeys();
}

