/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_FILE_BLOB_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_FILE_BLOB_H

#include <BaSyx/aas/api_v2/submodelelement/file/IBlob.h>
#include <BaSyx/aas/simple/submodelelement/SubmodelElement.h>

#include <vector>
#include <cstdint>

namespace basyx {
namespace aas {
namespace simple {
	
class Blob : 
	public api::IBlob,
	public SubmodelElement
{
private:
	BlobType data;
	MimeType mimeType;
public:
	Blob(const std::string & idShort, const std::string & mimeType);
	virtual ~Blob() = default;

	const BlobType & getValue() const override;
	void setValue(const BlobType & value) override;
	void setValue(BlobType && value) override;

	const MimeType getMimeType() const override;
	void setMimeType(const MimeType & mimeType) override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_FILE_BLOB_H */
