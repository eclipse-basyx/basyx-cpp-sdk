########################################
###             util                 ###
########################################
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set (BASYX_UTIL_LIB_SUFFIX "Util")

set (BASYX_UTIL_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_UTIL_LIB_SUFFIX}")

set (BASYX_UTIL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${BASYX_UTIL_LIB_SUFFIX})

set_target_properties(${BASYX_UTIL_LIB_SUFFIX}
   PROPERTIES VERSION ${PROJECT_VERSION}
)
#set_target_properties(${BASYX_UTIL_LIB_SUFFIX}
#   PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR}
#)
set_target_properties(${BASYX_UTIL_LIB_SUFFIX}
   PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}"
)

target_sources(${BASYX_UTIL_LIB_SUFFIX}
   PRIVATE
)

add_subdirectory(util)

target_include_directories(${BASYX_UTIL_LIB_SUFFIX}
   PUBLIC
   $<BUILD_INTERFACE:${BASYX_UTIL_INCLUDE_DIR}>
   $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_link_libraries(${BASYX_UTIL_LIB_SUFFIX}
   PUBLIC
)

add_library(BaSyx::libutil ALIAS ${BASYX_UTIL_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_UTIL_LIB_SUFFIX} ALIAS ${BASYX_UTIL_LIB_SUFFIX})

build_source_group()

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

install(DIRECTORY "${BASYX_UTIL_INCLUDE_DIR}/util"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_INCLUDENAME}"
        FILES_MATCHING PATTERN "*.h"
        PATTERN "*.hpp"
)
endif()

diagnostics_print(${BASYX_UTIL_LIB_SUFFIX})
