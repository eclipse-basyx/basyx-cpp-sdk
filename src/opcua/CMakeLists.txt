###############################################
###              BaSyx::OPCUA                 ###
###############################################

set (BASYX_OPCUA_LIB_SUFFIX "OPCUA")

set (BASYX_OPCUA_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_OPCUA_LIB_SUFFIX}")

set (BASYX_OPCUA_LIBRARY_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/opcua")

add_library(${BASYX_OPCUA_LIBRARY_NAME})

set_target_properties(${BASYX_OPCUA_LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_OPCUA_LIBRARY_NAME} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})

target_sources(${BASYX_OPCUA_LIBRARY_NAME}
  PRIVATE
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/api_v2/ApiAssetAdminstrationShell.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/api_v2/ApiSubmodel.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/api_v2/ApiProperty.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/api_v2/ApiHelpers.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/api_v2/ApiMetamodelUtilities.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASObjectDeserializer.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASModelProviderCommon.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASProviderApiParseHelpers.h
	${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASAggregatorProvider.h
	${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASSubmodelProvider.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASAggregatorHelpers.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/provider/AASSubmodelHelpers.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASAdministrativeInformationType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASAssetType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASAssetAdministrationShellType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASBlobType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASCapabilityType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASEventType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASFileType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASIdentifierType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASMetamodelAliases.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASMetamodel.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASMultiLanguagePropertyType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASOperationType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASOrderedSubmodelElementCollectionType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASPropertyType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASQualifierType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASRangeType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASReference.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASReferenceElementType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASReferenceType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASSubmodelElementCollectionType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASSubmodelElementType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/AASSubmodelType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/DictionaryEntryFragmentedId.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/DictionaryEntryIdShort.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/IAASIdentifiableType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/metamodel/IAASReferableType.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/node/MetamodelNodeUtils.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/node/MetamodelTypes.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/node/ModelNodeManager.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/node/AssetAdministrationShellNodeManager.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/node/PropertyNodeManager.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/aas/node/SubmodelNodeManager.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/NodeCommon.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/Utilities.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/BrowseName.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/LocalizedText.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/BrowsePath.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/NodeDescription.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/NodeId.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/ExpandedNodeId.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/QualifiedName.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/ObjectAttributes.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/ObjectTypeAttributes.h
	${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/ReferenceTypeAttributes.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/VariableAttributes.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/MethodAttributes.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/Variant.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/common/Services.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/client/Client.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/client/ClientServices.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/client/Subscription.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/client/open62541Client.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/server/Server.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/server/ServerServices.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/server/open62541Server.h
	${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/typesmap/TypesMap.h
	${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/typesmap/TypesTransformer.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/provider/OPCUAModelProvider.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/provider/OPCUAModelProviderHelpers.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/provider/OPCUA2VabHandlers.h
    ${BASYX_OPCUA_LIBRARY_INCLUDE_DIR}/provider/VAB2OPCUAHandlers.h
)

target_sources(${BASYX_OPCUA_LIBRARY_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/client/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/client/ClientServices.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/client/Subscription.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Utilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/NodeId.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/LocalizedText.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/ExpandedNodeId.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/QualifiedName.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/ObjectAttributes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/ObjectTypeAttributes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/ReferenceTypeAttributes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/VariableAttributes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/MethodAttributes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Variant.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/ServerServices.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Services.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASIdentifierType.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASAssetType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASAdministrativeInformationType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/IAASIdentifiableType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/IAASReferableType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/DictionaryEntryFragmentedId.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/DictionaryEntryIdShort.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASSubmodelType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASReference.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASReferenceType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASBlobType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASFileType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASQualifierType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASEventType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASRangeType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASSubmodelElementType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASCapabilityType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASPropertyType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASMultiLanguagePropertyType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASSubmodelType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASOperationType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASOrderedSubmodelElementCollectionType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASSubmodelElementCollectionType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASReferenceElementType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aas/metamodel/AASAssetAdministrationShellType.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/aas/api_v2/ApiHelpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/aas/api_v2/ApiMetamodelUtilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/aas/provider/AASModelProviderCommon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/aas/provider/AASProviderApiParseHelpers.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/typesmap/TypesMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/provider/OPCUAModelProvider.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/typesmap/TypesTransformer.cpp
)

target_include_directories(${BASYX_OPCUA_LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_OPCUA_LIBRARY_NAME} BaSyx::Shared BaSyx::Abstraction BaSyx::VAB BaSyx::AAS lib::open62541)
add_library(${PROJECT_SHORTNAME}::${BASYX_OPCUA_LIB_SUFFIX} ALIAS ${BASYX_OPCUA_LIBRARY_NAME})
add_library(basyx::opcua ALIAS ${BASYX_OPCUA_LIBRARY_NAME})

###############################################
###           Install section               ###
###############################################

configure_file("${BASYX_OPCUA_LIBRARY_NAME}Config.cmake.in" "${BASYX_OPCUA_LIBRARY_NAME}Config.cmake" @ONLY)

install(TARGETS ${BASYX_OPCUA_LIBRARY_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/opcua"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h")
        
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_OPCUA_LIBRARY_NAME}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_SHORTNAME})

diagnostics_print(${BASYX_OPCUA_LIBRARY_NAME})
build_source_group(${BASYX_OPCUA_LIBRARY_NAME})