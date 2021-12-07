/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/file/File.h>


namespace basyx {
namespace aas {
namespace map {

constexpr char File::Path::MimeType[];
constexpr char File::Path::Value[];

File::File(const std::string & idShort, const std::string & mimeType)
  : DataElement(idShort)
  , vab::ElementMap{}
{
	this->map.insertKey(Path::MimeType, mimeType);
	this->map.insertKey(Path::Value, std::string(""));
}

File::File(basyx::object obj)
  : vab::ElementMap{}
  , DataElement{obj}
{
  this->map.insertKey(Path::Value, obj.getProperty(Path::Value).GetStringContent());
  this->map.insertKey(Path::MimeType, obj.getProperty(Path::MimeType).GetStringContent());
}

File::File(const File & other)
  : DataElement(other.getIdShort(), other.getKind())
  , vab::ElementMap(other.getMap())
{}

const PathType File::getPath() const
{
	return this->map.getProperty(Path::Value).Get<std::string&>();
}

void File::setPath(const PathType & path)
{
	this->map.insertKey(Path::Value, path);
}

const std::string File::getMimeType() const
{
	return this->map.getProperty(Path::MimeType).Get<std::string&>();
}

void File::setMimeType(const std::string & mimeType)
{
	this->map.insertKey(Path::MimeType, mimeType);
}

}
}
}
