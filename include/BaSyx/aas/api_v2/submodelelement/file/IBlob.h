/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_FILE_IBLOB_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_FILE_IBLOB_H

#include <BaSyx/aas/api_v2/submodelelement/IDataElement.h>
#include <BaSyx/aas/api_v2/reference/IReference.h>

#include <BaSyx/shared/types.h>

#include <cstdint>
#include <vector>

namespace basyx {
namespace aas {

namespace api {
	
class IBlob : public virtual IDataElement
{
public:
	using MimeType = std::string;
	using BlobType = std::vector<char>;
public:
	virtual ~IBlob() = 0;

	virtual const BlobType & getValue() const = 0;
	virtual void setValue(const BlobType & value) = 0;
	virtual void setValue(BlobType && value) = 0;

	virtual const MimeType getMimeType() const = 0;
	virtual void setMimeType(const MimeType & mimeType) = 0;

	virtual KeyElements getKeyElementType() const override { return KeyElements::Blob; };
};

inline IBlob::~IBlob() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_FILE_IBLOB_H */
