#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>

#include <basyx/modeltype.h>

#include <basyx/submodelelement/property.h>

#include <basyx/util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

template<typename DataType>
class Range : public DataElement, private ModelType<ModelTypes::Range>
{
private:
	util::optional<DataType> min;
	util::optional<DataType> max;
public:
	Range(util::string_view idShort) : DataElement(idShort) {};

	Range(const Range&) = default;
	Range& operator=(const Range&) = default;

	Range(Range&&) = default;
	Range& operator=(Range&&) = default;

	~Range() = default;
public:
	const util::optional<DataType> & get_min() const { return this->min; };
	util::optional<DataType> & get_min() { return this->min; };

	const util::optional<DataType> & get_max() const { return this->max; };
	util::optional<DataType> & get_max() { return this->max; };

	util::string_view get_value_type() const { return detail::data_type_def<DataType>::value_type; };

	template<typename U = DataType>
	void set_min(U && value) {
		this->min.emplace(std::forward<U>(value));
	};

	template<typename U = DataType>
	void set_max(U && value) {
		this->max.emplace(std::forward<U>(value));
	};
};

}