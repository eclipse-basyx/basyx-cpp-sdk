/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

//#include <BaSyx/aas/map_v2/common/ModelType.h>
//
//using namespace basyx::aas;
//using namespace basyx::aas::map;
//
//
////ModelType::ModelType(ModelTypes modelType)
////{
////	auto modelTypeMap = basyx::object::make_map();
////	modelTypeMap.insertKey("name", ModelTypes_::to_string(modelType));
////	this->map.insertKey("modelType", modelTypeMap);
////};
////
////ModelTypes basyx::aas::map::ModelType::GetModelType() const
////{
////	auto modelType = this->map.getProperty("modelType").getProperty("name").Get<std::string&>();
////	return ModelTypes_::from_string(modelType);
////};