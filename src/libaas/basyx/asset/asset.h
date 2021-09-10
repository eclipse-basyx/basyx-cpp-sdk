#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/submodel.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/views/view.h>

#include <util/optional/optional.hpp>

namespace basyx
{

class Asset : 
	public Identifiable, 
	public ModelType<ModelTypes::Asset>
{
private:
public:
	Asset(util::string_view idShort, Identifier identifier) : Identifiable(idShort, std::move(identifier)) {};
	Asset(util::string_view idShort, util::string_view id) : Identifiable(idShort, id) {};
public:
	Asset(const Asset &) = default;
	Asset& operator=(const Asset &) = default;

	Asset(Asset &&) = default;
	Asset& operator=(Asset &&) = default;
};

};
