/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/file/File.h>

using namespace basyx::aas::simple;

File::File(const std::string & idShort, const std::string & mimeType)
	: SubmodelElement(idShort)
	, mimeType(mimeType)
{
};

const std::string File::getPath() const
{
	return this->path;
}

void File::setPath(const std::string & path)
{
	this->path = path;
}

const std::string File::getMimeType() const
{
	return this->mimeType;
}

void File::setMimeType(const std::string & mimeType)
{
	this->mimeType = mimeType;
}
