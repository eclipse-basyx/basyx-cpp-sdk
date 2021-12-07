/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_FILE_TYPE
#define AAS_FILE_TYPE

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASFileType
				{
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASFileType";
						static constexpr const char DisplayName[] = "AASFileType";
						static constexpr const char Description[] = "AASFileType";
						static constexpr const char NodeHandle[] = "AASFileType";

						static constexpr const char BrowseName_PropertyFileReference[] = "PropertyType::FileReference";
						static constexpr const char DisplayName_PropertyFileReference[] = "FileReference";
						static constexpr const char Description_PropertyFileReference[] = "AASFileType::PropertyType::FileReference";
						static constexpr const char NodeHandle_PropertyFileReference[] = "AASFileType::PropertyType::FileReference";

						static constexpr const char BrowseName_PropertyMimeType[] = "PropertyType::MimeType";
						static constexpr const char DisplayName_PropertyMimeType[] = "MimeType";
						static constexpr const char Description_PropertyMimeType[] = "AASFileType::PropertyType::MimeType";
						static constexpr const char NodeHandle_PropertyMimeType[] = "AASFileType::PropertyType::MimeType";

						static constexpr const char BrowseName_FileType[] = "FileType::File";
						static constexpr const char DisplayName_FileType[] = "File";
						static constexpr const char Description_FileType[] = "AASFileType::FileType";
						static constexpr const char NodeHandle_FileType[] = "AASFileType::FileType";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASFileType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId fileReference (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_PropertyFileReference);
					NodeId fileMIMEType  (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_PropertyMimeType);
					NodeId fileType      (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_FileType);

					status = services.addObjectTypeNode(
						getNodeId(t_ns),
						AASSubmodelElementType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASSUBTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText),
						ObjectTypeAttributes(AttrNames::DisplayName, AttrNames::Description, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addObjectNode(
						fileType,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_FILETYPE),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseName_FileType),
						ObjectAttributes(AttrNames::DisplayName_FileType, AttrNames::Description_FileType, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(fileType, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						fileReference,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseName_PropertyFileReference),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_PropertyFileReference, AttrNames::Description_PropertyFileReference, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(fileReference, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						fileMIMEType,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseName_PropertyMimeType),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_PropertyMimeType, AttrNames::Description_PropertyMimeType, "en-US")
					);


					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(fileMIMEType, UA_NODECLASS_VARIABLE);
				};
			}
		}
	}
}

#endif