#pragma once

#include <basyx/submodelelement/submodelelement.h>

#include <basyx/util/string_view/string_view.hpp>

namespace basyx
{

class DataElement : public SubmodelElement
{
public:
	DataElement(util::string_view idShort) : SubmodelElement(idShort) {};

	DataElement(const DataElement&) = default;
	DataElement& operator=(const DataElement&) = default;

	DataElement(DataElement&&) noexcept = default;
	DataElement& operator=(DataElement&&) noexcept = default;

	virtual ~DataElement() = default;
};

}
