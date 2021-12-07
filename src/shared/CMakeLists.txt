###############################################
###              BaSyx::Shared              ###
###############################################

set (BASYX_SHARED_LIB_SUFFIX "Shared")

set (BASYX_SHARED_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_SHARED_LIB_SUFFIX}")

set (BASYX_SHARED_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/shared")

set (BASYX_SHARED_TARGET_NAME "${BASYX_SHARED_LIB_SUFFIX}")

add_library(${BASYX_SHARED_TARGET_NAME})

set_target_properties(${BASYX_SHARED_TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_SHARED_TARGET_NAME} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_SHARED_TARGET_NAME} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
target_include_directories(${BASYX_SHARED_TARGET_NAME}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_sources(${BASYX_SHARED_TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/object/impl/obj_error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/object/impl/object_impl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared/serialization/json/typeid.cpp
)

target_sources(${BASYX_SHARED_TARGET_NAME}
    PRIVATE
        ${BASYX_SHARED_INCLUDE_DIR}/anyTypeChecker.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/bad_object_cast.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/impl/object_access_impl.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/impl/object_cast_impl.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/impl/object_factories_impl.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/impl/object_meta_impl.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/object_header.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/object_type.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/obj_function.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/obj_error.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/obj_holder.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/obj_placeholder.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/obj_error_holder.h
        ${BASYX_SHARED_INCLUDE_DIR}/object/obj_ref_holder.h
        ${BASYX_SHARED_INCLUDE_DIR}/object.h
        ${BASYX_SHARED_INCLUDE_DIR}/enums.h
        ${BASYX_SHARED_INCLUDE_DIR}/serialization/json/json.h
        ${BASYX_SHARED_INCLUDE_DIR}/serialization/json/json_deserializer.h
        ${BASYX_SHARED_INCLUDE_DIR}/serialization/json/json_serializer.h
        ${BASYX_SHARED_INCLUDE_DIR}/serialization/json/typeid.h
        ${BASYX_SHARED_INCLUDE_DIR}/serialization/json.h
        ${BASYX_SHARED_INCLUDE_DIR}/string_constants.h
        ${BASYX_SHARED_INCLUDE_DIR}/types.h
)

target_include_directories(${BASYX_SHARED_TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_SHARED_TARGET_NAME}
    PUBLIC
    BaSyx::Util
    BaSyx::Log
    nlohmann_json::nlohmann_json
)
add_library(basyx::shared ALIAS ${BASYX_SHARED_TARGET_NAME})
add_library(${PROJECT_SHORTNAME}::${BASYX_SHARED_LIB_SUFFIX} ALIAS ${BASYX_SHARED_TARGET_NAME})

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_SHARED_TARGET_NAME} PROPERTIES FOLDER BaSyx)
endif()

if(BASYX_VERBOSE_CMAKE_OUTPUT)
	diagnostics_print(${BASYX_SHARED_TARGET_NAME})
endif()

build_source_group(${BASYX_SHARED_TARGET_NAME})

###############################################
###           Install section               ###
###############################################
if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_SHARED_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_SHARED_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_SHARED_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_SHARED_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_SHARED_LIBRARY_NAME}
)

install(EXPORT ${BASYX_SHARED_LIB_SUFFIX}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_SHARED_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_SHARED_LIBRARY_NAME}
)

install(TARGETS ${BASYX_SHARED_TARGET_NAME}
        EXPORT ${BASYX_SHARED_LIB_SUFFIX}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${BASYX_INCLUDE_DIR}/${PROJECT_SHORTNAME}/shared"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h"
)

endif()
