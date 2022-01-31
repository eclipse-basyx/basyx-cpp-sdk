/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_FILE_BLOB_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_FILE_BLOB_H

#include <BaSyx/aas/api_v2/submodelelement/file/IBlob.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>

#include <base64.h>

#include <vector>
#include <cstdint>

namespace basyx {
namespace aas {
namespace map {
	
class Blob
  : public virtual api::IBlob
  , public virtual vab::ElementMap
  , public DataElement
  , public ModelType<ModelTypes::Blob>
{
public:
	struct Path {
		static constexpr char mimeType[] = "mimeType";
		static constexpr char value[] = "value";
	};

private:
	MimeType mimeType;
    BlobType rawData;
public:
	Blob(const std::string & idShort, const std::string & mimeType);
	Blob(basyx::object);

	virtual ~Blob() = default;

	const BlobType & getValue() const override;
	void setValue(const BlobType & value) override;
	void setValue(BlobType && value) override;

	const std::string getMimeType() const override;
	void setMimeType(const std::string & mimeType) override;

	KeyElements getKeyElementType() const override { return KeyElements::Blob; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_FILE_BLOB_H */
