/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_METAMODEL_ALIASES_H
#define AAS_METAMODEL_ALIASES_H

#include <BaSyx/shared/types.h>
#include <BaSyx/shared/object.h>
#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/api_v2/aas/IAssetAdministrationShell.h>
#include <BaSyx/aas/map_v2/aas/Asset.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/api_v2/submodelelement/property/IProperty.h>
#include <BaSyx/aas/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/aas/map_v2/qualifier/AdministrativeInformation.h>
#include <BaSyx/aas/map_v2/aas/Asset.h>
#include <BaSyx/aas/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/aas/enumerations/IdentifierType.h>
#include <BaSyx/aas/api_v2/qualifier/IAdministrativeInformation.h>
//Submodel
#include <BaSyx/aas/map_v2/Submodel.h>
#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>
#include <BaSyx/aas/map_v2/submodelelement/operation/Operation.h>
#include <BaSyx/aas/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/aas/api_v2/qualifier/IHasKind.h>
#include <BaSyx/aas/enumerations/KeyType.h>
#include <BaSyx/aas/enumerations/KeyElements.h>


namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			template<typename TYPE>
			using Collection = basyx::object::list_t<TYPE>;
			template<typename TYPE>
			using Collection_t = std::vector<std::shared_ptr<TYPE>>;

			template<typename t>
			using unique_collection_t = std::vector<std::unique_ptr<t>>;

			using Asset = basyx::aas::map::Asset;
			using IAssetAdministrationShell = basyx::aas::api::IAssetAdministrationShell;
			using AssetAdministrationShell = basyx::aas::map::AssetAdministrationShell;
			using AdminstrativeInformation = basyx::aas::map::AdministrativeInformation;
			using IProperty = basyx::aas::api::IProperty;
			template<typename TYPE>
			using Property_t = basyx::aas::map::Property<TYPE>;
			using Reference = basyx::aas::map::Reference;
			using Identifier = basyx::aas::simple::Identifier;
			//using IIdentifier = basyx::aas::simple::IIdentifier;
			using IdentifierType = basyx::aas::IdentifierType;
			using IAdministrativeInformation = basyx::aas::api::IAdministrativeInformation;
			using AdministrativeInformation = basyx::aas::simple::AdministrativeInformation;
			using ISubmodel = basyx::aas::api::ISubmodel;
			using Submodel = basyx::aas::map::Submodel;
			using ISubmodelElement = basyx::aas::api::ISubmodelElement;
			using IOperation = basyx::aas::api::IOperation;
			using Operation = basyx::aas::map::Operation;
			using IOperationVariable = basyx::aas::api::IOperationVariable;
			template<typename TYPE>
			using OperationVariable_t = basyx::aas::map::OperationVariable;
			using SubmodelElement = basyx::aas::map::SubmodelElement;
			using Kind = basyx::aas::ModelingKind;
			using KeyElements = basyx::aas::KeyElements;
			using KeyType = basyx::aas::KeyType;
			using Key = basyx::aas::simple::Key;
			using AASIdtype = IdentifierType;

			template<class IElementType>
			using IElementContainer = basyx::aas::api::IElementContainer<IElementType>;
			template<class IElementType>
			using ElementContainer = basyx::aas::map::ElementContainer<IElementType>;
			template<class IElementType>
			using ElementContainer_t = basyx::aas::map::ElementContainer<IElementType>;
		}
	}
}
#endif