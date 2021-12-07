/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/reference/Key.h>


namespace basyx {
namespace aas {
namespace simple {

Key::Key(KeyElements type, bool local, KeyType idType, const std::string & value)
	: type(type)
	, local(local)
	, idType(idType)
	, value(value)
{
}

KeyElements Key::getType() const noexcept
{
	return this->type;
}

KeyType Key::getIdType() const noexcept
{
	return this->idType;
}

bool Key::isLocal() const noexcept
{
	return local;
}

std::string Key::getValue() const noexcept
{
	return value;
}

bool Key::operator!=(const Key & other) const
{
	return this->idType != other.idType
		|| this->local != other.local
		|| this->type != other.type
		|| this->value != other.value;
};

bool Key::isModelKey() const noexcept
{
	return this->idType != basyx::aas::KeyType::IdShort;
};

bool Key::isGlobalKey() const noexcept
{
	return this->type != basyx::aas::KeyElements::GlobalReference;
};

}
}
}