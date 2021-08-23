#pragma once

#include <basyx/reference.h>

#include <util/optional/optional.hpp>

namespace basyx
{

class HasSemantics
{
private:
	util::optional<Reference> semanticId;
public:
	const util::optional<Reference> & getSemanticId() const { return this->semanticId; };
	util::optional<Reference> & getSemanticId() { return this->semanticId; };

	void setSemanticId(Reference semanticId) { this->semanticId = semanticId; };
	void setSemanticId(util::string_view semanticId) { this->semanticId = semanticId; };
};

};
