#pragma once

#include <basyx/modeltype.h>

namespace basyx
{
	
class Constraint : public virtual modeltype_base
{
public:
	Constraint() = default;
	virtual ~Constraint() = 0 {};
};

}