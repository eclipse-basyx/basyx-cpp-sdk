#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>

#include <basyx/serialization/serializable.h>

#include <string>

namespace basyx
{

class MultiLanguageProperty : 
	public DataElement, 
	private ModelType<ModelTypes::MultiLanguageProperty>,
	private serialization::Serializable<MultiLanguageProperty>
{
private:
	langstringset_t value;
	util::optional<Reference> valueId;
public:
	MultiLanguageProperty(util::string_view idShort) : DataElement(idShort) {};
	MultiLanguageProperty(util::string_view idShort, langstringset_t value) : DataElement(idShort), value(std::move(value)) {};

	MultiLanguageProperty(const MultiLanguageProperty&) = default;
	MultiLanguageProperty& operator=(const MultiLanguageProperty&) = default;

	MultiLanguageProperty(MultiLanguageProperty&&) = default;
	MultiLanguageProperty& operator=(MultiLanguageProperty&&) = default;

	~MultiLanguageProperty() = default;
public:
	using ModelType::get_model_type;
public:
	const util::optional<Reference> & get_value_id() const;
	void set_value_id(const Reference & reference);

	const langstringset_t & get_value() const;
	langstringset_t & get_value();
	void set_value(langstringset_t value);
public:
	util::optional<util::string_view> get_value(util::string_view language_code) const;
	void set_value(util::string_view language_code, util::string_view value);
};

}
