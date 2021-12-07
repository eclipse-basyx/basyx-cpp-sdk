###############################################
###              BaSyx::Logging             ###
###############################################
include(CMakePackageConfigHelpers)

set (BASYX_LOG_LIB_SUFFIX "Log")

set (BASYX_LOG_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_LOG_LIB_SUFFIX}")

set (BASYX_LOG_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/log")

add_library(${BASYX_LOG_LIB_SUFFIX})

set_target_properties(${BASYX_LOG_LIB_SUFFIX} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_LOG_LIB_SUFFIX} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_LOG_LIB_SUFFIX} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
target_include_directories(${BASYX_LOG_LIB_SUFFIX}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_sources(${BASYX_LOG_LIB_SUFFIX}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/log/log.cpp
)

target_sources(${BASYX_LOG_LIB_SUFFIX}
    PRIVATE
        ${BASYX_LOG_INCLUDE_DIR}/log.h
)                

target_include_directories(${BASYX_LOG_LIB_SUFFIX} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_LOG_LIB_SUFFIX}
    PUBLIC
        BaSyx::Util
        fmt::fmt
)

add_library(basyx::log ALIAS ${BASYX_LOG_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_LOG_LIB_SUFFIX} ALIAS ${BASYX_LOG_LIB_SUFFIX})

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_LOG_LIB_SUFFIX} PROPERTIES FOLDER BaSyx)
endif()

if(BASYX_VERBOSE_CMAKE_OUTPUT)
	diagnostics_print(${BASYX_LOG_LIB_SUFFIX})
endif()

build_source_group(${BASYX_LOG_LIB_SUFFIX})

###############################################
###           Install section               ###
###############################################
if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_LOG_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_LOG_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_LOG_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_LOG_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_LOG_LIBRARY_NAME}
)

install(EXPORT ${BASYX_LOG_LIB_SUFFIX}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_LOG_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_LOG_LIBRARY_NAME}
)

install(TARGETS ${BASYX_LOG_LIB_SUFFIX}
        EXPORT ${BASYX_LOG_LIB_SUFFIX}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${BASYX_INCLUDE_DIR}/${PROJECT_SHORTNAME}/log"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h"
)

endif()
