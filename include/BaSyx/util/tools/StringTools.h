/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef UTILITY_UTIL_TOOLS_STRINGTOOLS_H
#define UTILITY_UTIL_TOOLS_STRINGTOOLS_H

#include <string>
#include "CoderTools.h"

class StringTools {
public:
	/**
	 * Assumes the following layout:
	 * 4 byte size
	 * $size byte string content, not \0 terminated
	 */
	static std::string fromArray(char const* array) {
		size_t size = CoderTools::getInt32(array, 0);
		array += 4;
		return std::string(array, size);
	}

	/**
	 * Copies the content of str into target buffer without \0 termination
	 * Assumes that target is big enough to carry the content of str
	 */
	static std::size_t toArray(std::string const& str, char* target) {
		CoderTools::setInt32(target, 0, static_cast<uint32_t>(str.length()));
		target += 4;
		std::memcpy(target, str.c_str(), str.length());
		return str.length() + 4;
	}
};

#endif /* UTILITY_UTIL_TOOLS_STRINGTOOLS_H */
