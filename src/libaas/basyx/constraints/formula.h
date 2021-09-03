#pragma once

#include <basyx/constraints/constraint.h>

#include <basyx/modeltype.h>
#include <basyx/reference.h>

namespace basyx
{

class Formula : public Constraint, public ModelType<ModelTypes::Formula>
{
public:
	using dependsOn_t = std::vector<Reference>;
private:
	dependsOn_t dependsOn;
public:
	Formula() = default;

	Formula(const Formula&) = default;
	Formula& operator=(const Formula&) = default;

	Formula(Formula&&) = default;
	Formula& operator=(Formula&&) = default;

	~Formula() = default;
public:
	const dependsOn_t & getDependsOn() const { return this->dependsOn; };
	dependsOn_t & getDependsOn() { return this->dependsOn; };
	void setDependsOn(dependsOn_t dependsOn) { this->dependsOn = std::move(dependsOn); };
};

}