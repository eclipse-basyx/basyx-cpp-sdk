#pragma once

#include <basyx/reference.h>
#include <basyx/referable.h>
#include <basyx/haskind.h>
#include <basyx/hassemantics.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class SubmodelElement : public Referable, public HasKind, public HasSemantics, public virtual modeltype_base
{
protected:
	SubmodelElement(util::string_view idShort) : Referable(idShort) {};
public:
	SubmodelElement(const SubmodelElement&) = default;
	SubmodelElement& operator=(const SubmodelElement&) = default;

	SubmodelElement(SubmodelElement&&) noexcept = default;
	SubmodelElement& operator=(SubmodelElement&&) noexcept = default;

	virtual ~SubmodelElement() = default;
};

}