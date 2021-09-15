#pragma once

#include <basyx/enums/DataTypeIEC61360.h>
#include <basyx/enums/LevelType.h>

#include <basyx/reference.h>
#include <basyx/dataspecification/DataSpecification.h>
#include <basyx/langstringset.h>

#include <set>

namespace basyx {

class DataSpecificationIEC61360
{
private:
	langstringset_t preferredName;
	util::optional<langstringset_t> shortName;
	util::optional<langstringset_t> definition;

	util::optional<DataTypeIEC61360> dataType;
	util::optional<std::string> sourceOfDefinition;
	util::optional<std::string> symbol;
	util::optional<std::string> unit;
	util::optional<std::string> valueFormat;
	util::optional<Reference> unitId;
	//Reference valueList;
	std::set<LevelType> levelTypes;
public:
	DataSpecificationIEC61360(langstringset_t preferredName) : preferredName(std::move(preferredName)) {};
	DataSpecificationIEC61360(util::string_view langcode, util::string_view name) : preferredName(langcode, name) {};

	DataSpecificationIEC61360(const DataSpecificationIEC61360 &) = default;
	DataSpecificationIEC61360& operator=(const DataSpecificationIEC61360 &) = default;

	DataSpecificationIEC61360(DataSpecificationIEC61360 &&) noexcept = default;
	DataSpecificationIEC61360& operator=(DataSpecificationIEC61360 &&) noexcept = default;

	~DataSpecificationIEC61360() = default;
public:
	const langstringset_t & getPreferredName() const { return this->preferredName; };
	void setPreferredName(langstringset_t preferredName) { this->preferredName = std::move(preferredName); };
	
	const util::optional<langstringset_t> & getShortName() { return this->shortName; };
	void setShortName(langstringset_t shortName) { this->shortName = std::move(shortName); };

	const util::optional<langstringset_t> & getDefinition() { return this->definition; };
	void setShortName(langstringset_t definition) { this->definition = std::move(definition); };

	const util::optional<std::string> & getUnit() const { return this->unit; };
	void setUnit(util::string_view unit) { this->unit = unit; };

	const util::optional<Reference> & getUnitId() const { return this->unitId; };
	template<typename Ref> void setUnitId(Ref && unitId) { this->unitId = std::forward<T>(unitId); };

	const util::optional<std::string> & getSymbol() const { return this->symbol; };
	void setSymbol(util::string_view symbol) { this->symbol = symbol; };

	const util::optional<std::string> & getValueFormat() const { return this->valueFormat; };
	void setValueFormat(util::string_view valueFormat) { this->valueFormat = valueFormat; };

	const util::optional<std::string> & getSourceOfDefinition() const { return this->sourceOfDefinition; };
	void setSourceOfDefinition(util::string_view sourceOfDefinition) { this->sourceOfDefinition = sourceOfDefinition; };

	const util::optional<DataTypeIEC61360> & getDataType() const { return this->dataType; };
	void setDataType(DataTypeIEC61360 dataType) { this->dataType = dataType; };

	const std::set<LevelType> & getLevelTypes() const { return this->levelTypes; };
	std::set<LevelType> & getLevelTypes() { return this->levelTypes; };
};

}
