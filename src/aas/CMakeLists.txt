###############################################
###              BaSyx::AAS            ###
###############################################

include(CMakePackageConfigHelpers)

set (BASYX_AAS_LIB_SUFFIX "AAS")

set (BASYX_AAS_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_AAS_LIB_SUFFIX}")

set (BASYX_AAS_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/aas")
set (PROJECT_INCLUDE_DIR BASYX_AAS_INCLUDE_DIR)

add_library(${BASYX_AAS_LIB_SUFFIX})

set_target_properties(${BASYX_AAS_LIB_SUFFIX} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_AAS_LIB_SUFFIX} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_AAS_LIB_SUFFIX} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
target_include_directories(${BASYX_AAS_LIB_SUFFIX}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_sources(${BASYX_AAS_LIB_SUFFIX}
    PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/constexpr.cpp

	    ${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/AssetKind.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/DataTypeIEC61360.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/LevelType.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/ModelTypes.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/ModelingKind.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/EntityType.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/ReferableElements.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/LocalKeyType.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/IdentifierType.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/KeyType.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/KeyElements.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/IdentifiableElements.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/enumerations/XsdTypes.cpp
	
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/aas/AssetAdministrationShell.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/aas/Asset.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/common/LangStringSet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/common/ModelType.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/constraint/Formula.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/constraint/Qualifier.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/parts/ConceptDictionary.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/parts/ConceptDescription.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/parts/View.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/qualifier/AdministrativeInformation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/qualifier/HasDataSpecification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/qualifier/Identifiable.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/qualifier/Qualifiable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/qualifier/Referable.cpp        
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/reference/Reference.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/Submodel.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/AnnotatedRelationshipElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/BasicEvent.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/Capability.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/DataElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/Entity.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/RelationshipElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/operation/Operation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/operation/OperationVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/file/Blob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/file/File.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/property/MultiLanguageProperty.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/property/ReferenceElement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/SubmodelElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/SubmodelElementFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/submodelelement/SubmodelElementCollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/dataspecification/DataSpecification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/dataspecification/DataSpecificationIEC61360.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/dataspecification/ValueList.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/map_v2/dataspecification/DataSpecificationPhysicalUnit.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/aas/AssetAdministrationShell.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/aas/Asset.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/LangStringSet.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/Timezone.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/AnyURI.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/DateTime.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/Date.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/DayTimeDuration.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/YearMonthDuration.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/Time.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/GYearMonth.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/GYear.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/GMonthDay.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/GDay.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/common/xsd_types/GMonth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/constraint/Formula.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/constraint/Qualifier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/dataspecification/DataSpecification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/dataspecification/DataSpecificationIEC61360.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/dataspecification/DataSpecificationPhysicalUnit.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/dataspecification/ValueList.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/identifier/Identifier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/parts/ConceptDescription.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/parts/ConceptDictionary.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/parts/View.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/qualifier/AdministrativeInformation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/qualifier/HasDataSpecification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/qualifier/Identifiable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/qualifier/Qualifiable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/qualifier/Referable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/reference/Key.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/reference/Reference.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/Submodel.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/AnnotatedRelationshipElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/BasicEvent.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/DataElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/Capability.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/RelationshipElement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/file/Blob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/file/File.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/operation/Operation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/operation/OperationVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/property/MultiLanguageProperty.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/property/ReferenceElement.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/Entity.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/SubmodelElementCollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/aas/simple/submodelelement/SubmodelElement.cpp
    )


target_sources(${BASYX_AAS_LIB_SUFFIX}
    PRIVATE
        ${BASYX_AAS_INCLUDE_DIR}/enumerations/AssetKind.h
        ${BASYX_AAS_INCLUDE_DIR}/enumerations/DataTypeIEC61360.h
        ${BASYX_AAS_INCLUDE_DIR}/enumerations/LevelType.h
        ${BASYX_AAS_INCLUDE_DIR}/enumerations/ModelTypes.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/ModelingKind.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/EntityType.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/ReferableElements.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/LocalKeyType.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/IdentifierType.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/KeyType.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/KeyElements.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/IdentifiableElements.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/Conversions.h
		${BASYX_AAS_INCLUDE_DIR}/enumerations/XsdTypes.h
	
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/aas/IAssetAdministrationShell.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/aas/IAsset.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/common/IElementContainer.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/common/ILangStringSet.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/common/IModelType.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/dataspecification/IDataSpecificationContent.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/dataspecification/IDataSpecification.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/dataspecification/IDataSpecificationIEC61360.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/dataspecification/IValueList.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/dataspecification/IEmbeddedDataSpecification.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/dataspecification/IDataSpecificationPhysicalUnit.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/identifier/Identifier.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/constraint/IConstraint.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/constraint/IFormula.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/constraint/IQualifier.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/ISubmodel.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/parts/IConceptDescription.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/parts/IConceptDictionary.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/parts/IView.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IAdministrativeInformation.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IHasDataSpecification.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IHasKind.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IHasSemantics.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IIdentifiable.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IQualifiable.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/qualifier/IReferable.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/reference/IKey.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/reference/IReference.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/file/IBlob.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/file/IFile.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IDataElement.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IEntity.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/ISubmodelElementCollection.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/ISubmodelElement.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/operation/IOperation.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/operation/IOperationVariable.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/property/IMultiLanguageProperty.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/property/IProperty.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/property/XSDAnySimpleType.h
        ${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/property/IReferenceElement.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IRelationshipElement.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IAnnotatedRelationshipElement.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IEvent.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IBasicEvent.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/ICapability.h
		${BASYX_AAS_INCLUDE_DIR}/api_v2/submodelelement/IRange.h

        ${BASYX_AAS_INCLUDE_DIR}/map_v2/aas/AssetAdministrationShell.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/aas/Asset.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/common/ElementContainer.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/common/ElementListContainer.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/common/SubmodelContainer.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/common/ElementFactory.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/common/LangStringSet.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/common/ModelType.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/dataspecification/DataSpecificationIEC61360.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/dataspecification/DataSpecificationPhysicalUnit.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/dataspecification/DataSpecification.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/dataspecification/ValueList.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/parts/ConceptDictionary.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/parts/ConceptDescription.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/parts/View.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/constraint/Formula.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/constraint/Qualifier.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/qualifier/AdministrativeInformation.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/qualifier/HasDataSpecification.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/qualifier/Identifiable.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/qualifier/Qualifiable.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/qualifier/Referable.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/reference/Reference.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/AnnotatedRelationshipElement.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/BasicEvent.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/Capability.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/DataElement.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/Entity.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/Range.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/RelationshipElement.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/file/Blob.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/file/File.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/operation/Operation.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/operation/OperationVariable.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/property/MultiLanguageProperty.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/property/Property.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/property/ReferenceElement.h
        ${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/SubmodelElementCollection.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/SubmodelElementFactory.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/submodelelement/SubmodelElement.h
		${BASYX_AAS_INCLUDE_DIR}/map_v2/Submodel.h

        ${BASYX_AAS_INCLUDE_DIR}/simple/aas/AssetAdministrationShell.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/aas/Asset.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/common/ElementContainer.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/common/LangStringSet.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/Timezone.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/AnyURI.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/DateTime.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/Date.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/DayTimeDuration.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/YearMonthDuration.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/Time.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/GYearMonth.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/GYear.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/GMonthDay.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/GDay.h
		${BASYX_AAS_INCLUDE_DIR}/simple/common/xsd_types/GMonth.h
		${BASYX_AAS_INCLUDE_DIR}/simple/constraint/Formula.h
		${BASYX_AAS_INCLUDE_DIR}/simple/constraint/Qualifier.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/dataspecification/DataSpecification.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/dataspecification/DataSpecificationIEC61360.h
		${BASYX_AAS_INCLUDE_DIR}/simple/dataspecification/DataSpecificationPhysicalUnit.h
		${BASYX_AAS_INCLUDE_DIR}/simple/dataspecification/ValueReferencePair.h
		${BASYX_AAS_INCLUDE_DIR}/simple/dataspecification/ValueList.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/identifier/Identifier.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/parts/ConceptDescription.h
		${BASYX_AAS_INCLUDE_DIR}/simple/parts/ConceptDictionary.h
		${BASYX_AAS_INCLUDE_DIR}/simple/parts/View.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/qualifier/AdministrativeInformation.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/qualifier/HasDataSpecification.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/qualifier/Identifiable.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/qualifier/Qualifiable.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/qualifier/Referable.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/reference/Key.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/reference/Reference.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/AnnotatedRelationshipElement.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/BasicEvent.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/Capability.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/DataElement.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/RelationshipElement.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/file/Blob.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/file/File.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/operation/Operation.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/operation/OperationVariable.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/property/MultiLanguageProperty.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/property/Property.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/property/ReferenceElement.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/Entity.h
		${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/Range.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/SubmodelElementCollection.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/submodelelement/SubmodelElement.h
        ${BASYX_AAS_INCLUDE_DIR}/simple/Submodel.h
)

target_include_directories(${BASYX_AAS_LIB_SUFFIX} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_AAS_LIB_SUFFIX}
    PUBLIC
        BaSyx::Shared
        BaSyx::VAB
)

add_library(basyx::aas ALIAS ${BASYX_AAS_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_AAS_LIB_SUFFIX} ALIAS ${BASYX_AAS_LIB_SUFFIX})

# Disable inheritance by dominance warning in MSVC
if(MSVC)
	target_compile_options(${BASYX_AAS_LIB_SUFFIX} PUBLIC /wd4250)
endif()

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_AAS_LIB_SUFFIX} PROPERTIES FOLDER BaSyx)
endif()

if(BASYX_VERBOSE_CMAKE_OUTPUT)
	diagnostics_print(${BASYX_AAS_LIB_SUFFIX})
endif()

build_source_group(${BASYX_AAS_LIB_SUFFIX})

###############################################
###           Install section               ###
###############################################
if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_AAS_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_AAS_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_AAS_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_AAS_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_AAS_LIBRARY_NAME}
)

install(EXPORT ${BASYX_AAS_LIB_SUFFIX}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_AAS_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_AAS_LIBRARY_NAME}
)

install(TARGETS ${BASYX_AAS_LIB_SUFFIX}
        EXPORT ${BASYX_AAS_LIB_SUFFIX}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${BASYX_INCLUDE_DIR}/${PROJECT_SHORTNAME}/aas"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h"
)

endif()