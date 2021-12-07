/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/aas/simple/reference/Key.h>
#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>

using namespace basyx::aas;
using namespace basyx::aas::simple;
using namespace basyx::aas::api;


Reference::Reference(const Key & key) 
{
	keyList.emplace_back(key);
}

Reference::Reference(const std::vector<Key> & keys)
	: keyList(keys)
{
}

Reference::Reference(std::vector<Key> && keys)
	: keyList(keys)
{
}

Reference::Reference(const std::initializer_list<Key> keys)
	: keyList(keys)
{
}

Reference::Reference(const IReference & other)
	: keyList(std::move(other.getKeys()))
{
};

//Reference Reference::FromIdentifiable(KeyElements keyElementType, const IIdentifiable & identifiable)
//{
//	return Reference(
//		Key(keyElementType,
//			true,
//			static_cast<KeyType>(identifiable.getIdentification().getIdType()),
//			identifiable.getIdentification().getId()) );
//};

std::vector<Key> Reference::getKeys() const
{
	return keyList;
}

void Reference::addKey(const Key & key)
{
	this->keyList.emplace_back(key);
}

bool Reference::empty() const
{
	return this->keyList.empty();
}

bool Reference::operator!=(const Reference & other) const
{
	return this->keyList != other.keyList;
};

bool Reference::operator!=(const api::IReference & other) const
{
	return this->keyList != other.getKeys();
};

