########################################
###             util                 ###
########################################

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

target_include_directories(${BASYX_UTIL_LIB_SUFFIX}
   PUBLIC
   $<BUILD_INTERFACE:${BASYX_UTIL_INCLUDE_DIR}>
   $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_sources(${BASYX_UTIL_LIB_SUFFIX}
   PRIVATE
)

add_subdirectory(util)

target_include_directories(${BASYX_UTIL_LIB_SUFFIX} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_UTIL_LIB_SUFFIX}
   PUBLIC
)

add_library(BaSyx::libutil ALIAS ${BASYX_UTIL_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_UTIL_LIB_SUFFIX} ALIAS ${BASYX_UTIL_LIB_SUFFIX})

build_source_group()
diagnostics_print(${BASYX_UTIL_LIB_SUFFIX})
