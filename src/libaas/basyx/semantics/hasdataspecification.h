#pragma once

#include <basyx/reference.h>

#include <basyx/util/optional/optional.hpp>
#include <basyx/util/string_view/string_view.hpp>
#include <basyx/util/container/container.hpp>

#include <basyx/referable.h>
#include <basyx/hassemantics.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class HasDataSpecification
{
public:
	using dataSpecification_t = std::vector<Reference>;
private:
	dataSpecification_t dataSpecification;
public:
	HasDataSpecification() {};
public:
	HasDataSpecification(const HasDataSpecification &) = default;
	HasDataSpecification& operator=(const HasDataSpecification &) = default;

	HasDataSpecification(HasDataSpecification &&) noexcept = default;
	HasDataSpecification& operator=(HasDataSpecification &&) noexcept = default;
public:
	std::size_t size() const { return dataSpecification.size(); };
public:
	const dataSpecification_t & getDataSpecification() const { return dataSpecification; };
	dataSpecification_t & getContainedElments() { return dataSpecification; };
	void setDataSpecification(dataSpecification_t dataSpecification) { this->dataSpecification = std::move(dataSpecification); };
};

};
