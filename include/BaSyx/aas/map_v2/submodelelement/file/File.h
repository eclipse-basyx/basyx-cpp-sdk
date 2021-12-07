/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_FILE_FILE_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_FILE_FILE_H

#include <BaSyx/aas/api_v2/submodelelement/file/IFile.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>

#include <vector>
#include <cstdint>

namespace basyx {
namespace aas {
namespace map {
	
class File : 
	public virtual api::IFile, 
	public DataElement,
	public ModelType<ModelTypes::File>
{
public:
	struct Path {
		static constexpr char MimeType[] = "mimeType";
		static constexpr char Value[] = "value";
	};
public:
	File(const std::string & idShort, const std::string & mimeType);
	File(basyx::object);
	File(const File & other);

	virtual ~File() = default;

	const PathType getPath() const override;
	void setPath(const PathType & value) override;

	const std::string getMimeType() const override;
	void setMimeType(const std::string & mimeType) override;

	KeyElements getKeyElementType() const override { return KeyElements::File; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_FILE_FILE_H */
