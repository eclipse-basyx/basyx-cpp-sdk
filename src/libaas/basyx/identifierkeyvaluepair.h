#pragma once

#include <basyx/reference.h>

#include <util/optional/optional.hpp>
#include <util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class IdentifierKeyValuePair
{
private:
	std::string key;
	util::optional<std::string> value;
	util::optional<Reference> externalSubjectId;
public:
	IdentifierKeyValuePair(util::string_view key) : key(key.to_string()) {};

	IdentifierKeyValuePair(const IdentifierKeyValuePair&) = default;
	IdentifierKeyValuePair(IdentifierKeyValuePair&&) = default;

	IdentifierKeyValuePair & operator=(const IdentifierKeyValuePair&) noexcept = default;
	IdentifierKeyValuePair & operator=(IdentifierKeyValuePair&&) noexcept = default;

	~IdentifierKeyValuePair() = default;
public:
	const std::string & getKey() const { return key; };
	void setKey(util::string_view key) { this->key = key.to_string(); };

	const util::optional<std::string> & getValue() const { return this->value; };
	void setValue(util::string_view value) { this->value = value; }

	const util::optional<Reference> getExternalSubjectId() const { return this->getExternalSubjectId; };
	template<typename Ref> void setExternalSubjectId(Ref && ref) { this->externalSubjectId = std::forward<Ref>(ref); };
};

};
