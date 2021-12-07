/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_FILE_IFILE_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_FILE_IFILE_H

#include <BaSyx/aas/api_v2/submodelelement/IDataElement.h>
#include <BaSyx/aas/api_v2/reference/IReference.h>
#include <BaSyx/aas/api_v2/submodelelement/file/IBlob.h>

#include <BaSyx/shared/types.h>

namespace basyx {
namespace aas {

using PathType = std::string;

namespace api {

class IFile : public virtual IDataElement
{
public:
	virtual ~IFile() = 0;

	virtual const PathType getPath() const = 0;
	virtual void setPath(const PathType & path) = 0;

	virtual const std::string getMimeType() const = 0;
	virtual void setMimeType(const std::string & mimeType) = 0;

	virtual KeyElements getKeyElementType() const override { return KeyElements::File; };
};

inline IFile::~IFile() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_FILE_IFILE_H */
