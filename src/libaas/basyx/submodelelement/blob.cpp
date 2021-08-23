#include "multilanguageproperty.h"
#include "blob.h"

namespace basyx
{
	const std::string & Blob::getMimeType() const
	{
		return this->mimeType;
	}

	void Blob::setMimeType(util::string_view mimeType)
	{
		this->mimeType = mimeType.to_string();
	}

	const Blob::blobType_t & Blob::getBlob() const
	{
		return this->blobValue;
	}

	Blob::blobType_t & Blob::getBlob()
	{
		return this->blobValue;
	}

	void Blob::setBlob(blobType_t blob)
	{
		this->blobValue = std::move(blob);
	}

	Blob Blob::fromLocalFile(util::string_view idShort, util::string_view mimeType, util::string_view path)
	{
		Blob blob(idShort, mimeType);

		// ToDo: read from file here

		return blob;
	}
};