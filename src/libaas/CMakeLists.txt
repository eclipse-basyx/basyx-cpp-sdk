########################################
###               AAS                ###
########################################

set (BASYX_AAS_LIB_SUFFIX "AAS")

set (BASYX_AAS_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_AAS_LIB_SUFFIX}")

set (BASYX_AAS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${BASYX_AAS_LIB_SUFFIX})

set_target_properties(${BASYX_AAS_LIB_SUFFIX}
   PROPERTIES VERSION ${PROJECT_VERSION}
)
#set_target_properties(${BASYX_AAS_LIB_SUFFIX}
#   PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR}
#)
set_target_properties(${BASYX_AAS_LIB_SUFFIX}
   PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}"
)

target_include_directories(${BASYX_AAS_LIB_SUFFIX}
   PUBLIC
   $<BUILD_INTERFACE:${BASYX_AAS_INCLUDE_DIR}>
   $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
)

add_subdirectory(basyx)

target_include_directories(${BASYX_AAS_LIB_SUFFIX} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_AAS_LIB_SUFFIX}
   PUBLIC
   BaSyx::libutil
   nlohmann_json::nlohmann_json
   pugixml::pugixml
)

add_library(BaSyx::libaas ALIAS ${BASYX_AAS_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_AAS_LIB_SUFFIX} ALIAS ${BASYX_AAS_LIB_SUFFIX})

build_source_group()
diagnostics_print(${BASYX_AAS_LIB_SUFFIX})
