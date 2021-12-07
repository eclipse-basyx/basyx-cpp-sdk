/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/common/ModelType.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>
#include <BaSyx/aas/api_v2/submodelelement/property/XSDAnySimpleType.h>

using namespace basyx::aas::map;

constexpr char ModelTypePath::Name[];
constexpr char ModelTypePath::ModelType[];

constexpr char ElementContainerPath::IdShort[];

constexpr char PropertyPath::Value[];
constexpr char PropertyPath::ValueType[];
constexpr char PropertyPath::ValueId[];

constexpr char basyx::xsd_types::xsd_type<basyx::aas::simple::DateTime>::format[];
constexpr char basyx::xsd_types::xsd_type<basyx::aas::simple::Date>::format[];
