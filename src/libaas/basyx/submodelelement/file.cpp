#include "file.h"

namespace basyx
{
	const util::optional<std::string>& File::getValue() const
	{
		return this->value;
	}

	util::optional<std::string>& File::getValue()
	{
		return this->value;
	}

	void File::setValue(util::string_view value)
	{
		this->value = value.to_string();
	}

	const std::string & File::getMimeType() const
	{
		return this->mimeType;
	}

	std::string & File::getMimeType()
	{
		return this->mimeType;
	}

	void File::setMimeType(util::string_view mimeType)
	{
		this->mimeType = mimeType.to_string();
	}
};