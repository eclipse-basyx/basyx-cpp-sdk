/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/qualifier/Referable.h>
#include <BaSyx/aas/simple/reference/Reference.h>

using namespace basyx::aas::simple;
using namespace basyx::aas::api;

Referable::Referable(const std::string & idShort, Referable * parent)
	: idShort(idShort)
	, parent(parent)
{}

Referable::Referable(const IReferable &other)
  : idShort(other.getIdShort())
  , category(*other.getCategory())
  , description(other.getDescription())
  , parent(other.getParent())
{};

const std::string & Referable::getIdShort() const
{
	return this->idShort;
}

const std::string * const Referable::getCategory() const
{
	if (this->category.empty())
		return nullptr;

	return &this->category;
}

LangStringSet & Referable::getDescription()
{
	return this->description;
}

const LangStringSet & Referable::getDescription() const
{
	return this->description;
}

void Referable::setIdShort(const std::string & idShort)
{
	this->idShort = idShort;
}

void Referable::setCategory(const std::string & category)
{
	this->category = category;
}

IReferable * Referable::getParent() const
{
	return this->parent;
};

void Referable::setParent(IReferable * parent)
{
	this->parent = parent;
};

bool Referable::hasParent() const noexcept
{
	return this->parent != nullptr;
};

bool Referable::hasDescription() const noexcept
{
	return !this->description.empty();
};

bool Referable::hasCategory() const noexcept 
{
	return !this->category.empty();
}

Reference Referable::getReference() const
{
	auto key = simple::Key(KeyElements::AssetAdministrationShell, true, KeyType::IdShort, this->getIdShort());

	if (this->getParent() == nullptr)
		return simple::Reference(key);

	auto reference = this->getParent()->getReference();

	reference.addKey(key);

	return reference;
}

basyx::aas::KeyElements Referable::getKeyElementType() const
{
	return basyx::aas::KeyElements::Unknown;
}

basyx::aas::simple::Key Referable::getKey(bool local) const
{
	return basyx::aas::simple::Key(this->getKeyElementType(), local, this->getKeyType(), this->getIdShort());
}