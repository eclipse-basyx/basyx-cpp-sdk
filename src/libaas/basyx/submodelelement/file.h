#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>

#include <basyx/util/string_view/string_view.hpp>

#include <basyx/serialization/serializable.h>

#include <string>

namespace basyx
{

class File : 
	public DataElement, 
	private ModelType<ModelTypes::File>,
	private serialization::Serializable<File>
{
private:
	std::string mimeType;
	util::optional<std::string> value;
public:
	File(util::string_view idShort, util::string_view mimeType) : DataElement(idShort), mimeType(mimeType.to_string()) {};
	File(util::string_view idShort, util::string_view mimeType, util::string_view value) 
		: DataElement(idShort), mimeType(mimeType.to_string()), value(value.to_string()) {};

	File(const File&) = default;
	File& operator=(const File&) = default;

	File(File&&) = default;
	File& operator=(File&&) = default;

	~File() = default;
public:
	using ModelType::get_model_type;
public:
	const util::optional<std::string> & getValue() const;
	util::optional<std::string> & getValue();
	void setValue(util::string_view value);

	const std::string & getMimeType() const;
	std::string & getMimeType();
	void setMimeType(util::string_view mimeType);
};

}
