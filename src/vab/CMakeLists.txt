###############################################
###              BaSyx::VAB                 ###
###############################################
include(CMakePackageConfigHelpers)

set (BASYX_VAB_LIB_SUFFIX "VAB")

set (BASYX_VAB_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_VAB_LIB_SUFFIX}")

set (BASYX_VAB_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/vab")

add_library(${BASYX_VAB_LIB_SUFFIX})

set_target_properties(${BASYX_VAB_LIB_SUFFIX} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_VAB_LIB_SUFFIX} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_VAB_LIB_SUFFIX} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
target_include_directories(${BASYX_VAB_LIB_SUFFIX}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

if(${BASYX_DEBUG_PRINT_FRAMES})
    target_compile_definitions(${BASYX_VAB_LIB_SUFFIX} PUBLIC PRINT_FRAME)
endif()

target_sources(${BASYX_VAB_LIB_SUFFIX}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/backend/connector/native/BaSyxConnector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/backend/connector/native/frame/Frame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/backend/connector/native/frame/EntityWrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/core/proxy/VABElementProxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/core/util/VABPath.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/core/VABConnectionManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/provider/VABModelProvider.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/provider/native/frame/BaSyxNativeFrameProcessor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vab/ElementMap.cpp
)


target_sources(${BASYX_VAB_LIB_SUFFIX}
    PRIVATE
        ${BASYX_VAB_INCLUDE_DIR}/backend/connector/IBaSyxConnector.h
        ${BASYX_VAB_INCLUDE_DIR}/backend/connector/JSONProvider.h
        ${BASYX_VAB_INCLUDE_DIR}/backend/connector/native/BaSyxConnector.h
        ${BASYX_VAB_INCLUDE_DIR}/backend/connector/native/frame/Frame.h
        ${BASYX_VAB_INCLUDE_DIR}/backend/connector/native/frame/EntityWrapper.h
        ${BASYX_VAB_INCLUDE_DIR}/core/IModelProvider.h
        ${BASYX_VAB_INCLUDE_DIR}/core/proxy/IVABElementProxy.h
        ${BASYX_VAB_INCLUDE_DIR}/core/proxy/VABElementProxy.h
        ${BASYX_VAB_INCLUDE_DIR}/core/util/VABPath.h
        ${BASYX_VAB_INCLUDE_DIR}/core/VABConnectionManager.h
        ${BASYX_VAB_INCLUDE_DIR}/ElementMap.h
        ${BASYX_VAB_INCLUDE_DIR}/provider/hashmap/VABHashmapProvider.h
        ${BASYX_VAB_INCLUDE_DIR}/provider/IVABElementHandler.h
        ${BASYX_VAB_INCLUDE_DIR}/provider/native/frame/BaSyxNativeFrameHelper.h
        ${BASYX_VAB_INCLUDE_DIR}/provider/native/frame/BaSyxNativeFrameProcessor.h
        ${BASYX_VAB_INCLUDE_DIR}/provider/VABModelProvider.h
        ${BASYX_VAB_INCLUDE_DIR}/provider/VABMultiElementHandler.h
)


target_include_directories(${BASYX_VAB_LIB_SUFFIX} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_VAB_LIB_SUFFIX}
    PUBLIC
    BaSyx::Shared
    BaSyx::Abstraction
)

add_library(basyx::vab ALIAS ${BASYX_VAB_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_VAB_LIB_SUFFIX} ALIAS ${BASYX_VAB_LIB_SUFFIX})

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_VAB_LIB_SUFFIX} PROPERTIES FOLDER BaSyx)
endif()

if(BASYX_VERBOSE_CMAKE_OUTPUT)
	diagnostics_print(${BASYX_VAB_LIB_SUFFIX})
endif()

build_source_group(${BASYX_VAB_LIB_SUFFIX})

###############################################
###           Install section               ###
###############################################
if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_VAB_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_VAB_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_VAB_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_VAB_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_VAB_LIBRARY_NAME}
)

install(EXPORT ${BASYX_VAB_LIB_SUFFIX}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_VAB_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_VAB_LIBRARY_NAME}
)

install(TARGETS ${BASYX_VAB_LIB_SUFFIX}
        EXPORT ${BASYX_VAB_LIB_SUFFIX}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${BASYX_INCLUDE_DIR}/${PROJECT_SHORTNAME}/vab"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h"
)

endif()
