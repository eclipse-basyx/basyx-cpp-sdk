#pragma once

#include <basyx/constraints/constraint.h>

#include <vector>

namespace basyx
{

class Qualifiable
{
public:
	using constraintPtr_t = std::unique_ptr<Constraint>;
	using qualifierList_t = std::vector<constraintPtr_t>;
private:
	qualifierList_t qualifierList;
public:
	Qualifiable() = default;

	Qualifiable(const Qualifiable&) = default;
	Qualifiable(Qualifiable&&) = default;

	Qualifiable & operator=(const Qualifiable&) = default;
	Qualifiable & operator=(Qualifiable&&) = default;

	~Qualifiable() = default;
public:
	const qualifierList_t & getQualifiers() const { return this->qualifierList; };
	qualifierList_t & getQualifiers() { return this->qualifierList; };

	template<typename U>
	Constraint * addQualifier(U && u) {
		auto qualifier = std::make_unique<U>(std::forward(u));
		qualifierList.emplace_back(std::move(qualifier));
		return qualifierList.back().get();
	}
};

};
