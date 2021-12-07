/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_IDENTIFIER_IDENTIFIER_H
#define BASYX_SUBMODEL_SIMPLE_IDENTIFIER_IDENTIFIER_H

#include <BaSyx/aas/enumerations/IdentifierType.h>

#include <string>

namespace basyx {
namespace aas {
namespace simple {

class Identifier
{
public:
	Identifier();
	Identifier(IdentifierType idType, const std::string & id);
	~Identifier() = default;
private:
	IdentifierType idType;
	std::string id;
public:
	static Identifier Custom(const std::string & id);
	static Identifier URI(const std::string & uri);
	static Identifier IRDI(const std::string & irdi);
public:
	IdentifierType getIdType() const;
	const std::string & getId() const;


  friend bool operator==(const Identifier & left, const Identifier & right);
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_IDENTIFIER_IDENTIFIER_H */
