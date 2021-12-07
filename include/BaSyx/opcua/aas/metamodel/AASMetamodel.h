/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_METAMODEL_H
#define AAS_METAMODEL_H

#include <unordered_map>
#include <BaSyx/log/log.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/metamodel/AASIdentifierType.h>
#include <BaSyx/opcua/aas/metamodel/AASAssetType.h>
#include <BaSyx/opcua/aas/metamodel/AASAdministrativeInformationType.h>
#include <BaSyx/opcua/aas/metamodel/IAASIdentifiableType.h>
#include <BaSyx/opcua/aas/metamodel/IAASReferableType.h>
#include <BaSyx/opcua/aas/metamodel/AASReference.h>
#include <BaSyx/opcua/aas/metamodel/AASReferenceType.h>
#include <BaSyx/opcua/aas/metamodel/AASBlobType.h>
#include <BaSyx/opcua/aas/metamodel/AASFileType.h>
#include <BaSyx/opcua/aas/metamodel/AASQualifierType.h>
#include <BaSyx/opcua/aas/metamodel/AASEventType.h>
#include <BaSyx/opcua/aas/metamodel/AASRangeType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>
#include <BaSyx/opcua/aas/metamodel/AASCapabilityType.h>
#include <BaSyx/opcua/aas/metamodel/AASPropertyType.h>
#include <BaSyx/opcua/aas/metamodel/AASMultiLanguagePropertyType.h>
#include <BaSyx/opcua/aas/metamodel/AASReferenceElementType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelType.h>
#include <BaSyx/opcua/aas/metamodel/AASAssetAdministrationShellType.h>
#include <BaSyx/opcua/aas/metamodel/AASOperationType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementCollectionType.h>
#include <BaSyx/opcua/aas/metamodel/AASOrderedSubmodelElementCollectionType.h>
#include <BaSyx/opcua/aas/metamodel/DictionaryEntryFragmentedId.h>
#include <BaSyx/opcua/aas/metamodel/DictionaryEntryIdShort.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASMetamodel
				{
					template<typename CONNECTOR_TYPE>
					static void define(int32_t t_ns, CONNECTOR_TYPE & t_connector);
				};

				template<typename CONNECTOR_TYPE>
				inline void AASMetamodel::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					DictionaryEntryFragmentedId::define<CONNECTOR_TYPE>(t_ns, t_connector);
					DictionaryEntryIdShort::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASAdministrativeInformationType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					IAASReferableType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASIdentifierType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					IAASIdentifiableType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASReference::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASReferenceType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASQualifierType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASSubmodelElementType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASBlobType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASFileType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASEventType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASCapabilityType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASRangeType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASPropertyType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASMultiLanguagePropertyType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASReferenceElementType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASSubmodelType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					//AASAssetType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASAssetAdministrationShellType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASOperationType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASSubmodelElementCollectionType::define<CONNECTOR_TYPE>(t_ns, t_connector);
					AASOrderedSubmodelElementCollectionType::define<CONNECTOR_TYPE>(t_ns, t_connector);
				}
			}
		}
	}
}

#endif