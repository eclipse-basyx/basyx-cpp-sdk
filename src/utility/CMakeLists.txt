###############################################
###              BaSyx::Util                ###
###############################################
include(CMakePackageConfigHelpers)

set (BASYX_UTIL_LIB_SUFFIX "Util")

set (BASYX_UTIL_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_UTIL_LIB_SUFFIX}")

set (BASYX_UTIL_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/util")

add_library(${BASYX_UTIL_LIB_SUFFIX})

set_target_properties(${BASYX_UTIL_LIB_SUFFIX} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_UTIL_LIB_SUFFIX} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_UTIL_LIB_SUFFIX} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
target_include_directories(${BASYX_UTIL_LIB_SUFFIX}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_sources(${BASYX_UTIL_LIB_SUFFIX}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/util/util.cpp
)

target_sources(${BASYX_UTIL_LIB_SUFFIX}
    PRIVATE
        ${BASYX_UTIL_INCLUDE_DIR}/function_traits.h
        ${BASYX_UTIL_INCLUDE_DIR}/invoke.h
        ${BASYX_UTIL_INCLUDE_DIR}/macros.h
        ${BASYX_UTIL_INCLUDE_DIR}/make_function.h
        ${BASYX_UTIL_INCLUDE_DIR}/meta.h
        ${BASYX_UTIL_INCLUDE_DIR}/printer.h
        ${BASYX_UTIL_INCLUDE_DIR}/tools/CoderTools.h
        ${BASYX_UTIL_INCLUDE_DIR}/tools/StringTools.h
        ${BASYX_UTIL_INCLUDE_DIR}/util.h
)

target_include_directories(${BASYX_UTIL_LIB_SUFFIX} PRIVATE ${PROJECT_SOURCE_DIR})

add_library(basyx::util ALIAS ${BASYX_UTIL_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_UTIL_LIB_SUFFIX} ALIAS ${BASYX_UTIL_LIB_SUFFIX})

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_UTIL_LIB_SUFFIX} PROPERTIES FOLDER BaSyx)
endif()

if(BASYX_VERBOSE_CMAKE_OUTPUT)
	diagnostics_print(${BASYX_UTIL_LIB_SUFFIX})
endif()

build_source_group(${BASYX_UTIL_LIB_SUFFIX})

###############################################
###           Install section               ###
###############################################
if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_UTIL_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_UTIL_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_UTIL_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_UTIL_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_UTIL_LIBRARY_NAME}
)

install(EXPORT ${BASYX_UTIL_LIB_SUFFIX}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_UTIL_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_UTIL_LIBRARY_NAME}
)

install(TARGETS ${BASYX_UTIL_LIB_SUFFIX}
        EXPORT ${BASYX_UTIL_LIB_SUFFIX}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${BASYX_INCLUDE_DIR}/${PROJECT_SHORTNAME}/util"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h"
)

endif()