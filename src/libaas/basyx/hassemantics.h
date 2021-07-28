#pragma once

#include <basyx/reference.h>

#include <util/optional/optional.hpp>

namespace basyx
{

class HasSemantics
{
public:
	util::optional<Reference> semanticId;
};

};
