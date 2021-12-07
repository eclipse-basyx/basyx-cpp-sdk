/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef UTIL_META_H
#define UTIL_META_H

namespace util {
	namespace meta {

		template<typename... Ts>
		struct Typelist {
		};

		template<int...>
		struct sequence { };

		template<int head, int... tail>
		struct generator_sequence : generator_sequence<head - 1, head - 1, tail...> { };

		template<int... tail>
		struct generator_sequence<0, tail...> {
			typedef sequence<tail...> type;
		};

	}
};

#endif // UTIL_META_H