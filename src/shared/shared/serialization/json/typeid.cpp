/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/shared/serialization/json/typeid.h>



constexpr char basyx::serialization::basysType<bool>::string[];
constexpr char basyx::serialization::basysType<int>::string[];
constexpr char basyx::serialization::basysType<float>::string[];
constexpr char basyx::serialization::basysType<double>::string[];
constexpr char basyx::serialization::basysType<char>::string[];
constexpr char basyx::serialization::basysType<std::string>::string[];
