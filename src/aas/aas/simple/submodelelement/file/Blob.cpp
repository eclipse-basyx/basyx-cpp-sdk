/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/file/Blob.h>

using namespace basyx::aas::simple;

Blob::Blob(const std::string & idShort, const std::string & mimeType)
	: SubmodelElement(idShort)
	, mimeType(mimeType)
{
};

const Blob::BlobType & Blob::getValue() const
{
	return this->data;
}

void Blob::setValue(const BlobType & value)
{
	this->data = value;
}

void Blob::setValue(BlobType && value)
{
	this->data = std::move(value);
}


const Blob::MimeType Blob::getMimeType() const
{
	return this->mimeType;
}

void Blob::setMimeType(const Blob::MimeType & mimeType)
{
	this->mimeType = mimeType;
}
