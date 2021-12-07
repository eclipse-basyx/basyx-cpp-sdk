###############################################
###              BaSyx::Server              ###
###############################################
include(CMakePackageConfigHelpers)

set (BASYX_SERVER_LIB_SUFFIX "Server")

set (BASYX_SERVER_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_SERVER_LIB_SUFFIX}")
set (BASYX_SHARED_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/server")

add_library(${BASYX_SERVER_LIB_SUFFIX})

set_target_properties(${BASYX_SERVER_LIB_SUFFIX} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_SERVER_LIB_SUFFIX} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_SERVER_LIB_SUFFIX} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
target_include_directories(${BASYX_SERVER_LIB_SUFFIX}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

if(${BASYX_DEBUG_PRINT_FRAMES})
    target_compile_definitions(${BASYX_SERVER_LIB_SUFFIX} PUBLIC PRINT_FRAME)
endif()

target_sources(${BASYX_SERVER_LIB_SUFFIX}
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/server/TCPServer.cpp
    ${BASYX_SHARED_INCLUDE_DIR}/TCPServer.h
    ${BASYX_SHARED_INCLUDE_DIR}/BaSyxNativeProvider.h
)

# TCPSelectServer currently only supported under UNIX
if(UNIX)
	target_sources(${BASYX_SERVER_LIB_SUFFIX} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/server/TCPSelectServer.cpp)
endif()

target_include_directories(${BASYX_SERVER_LIB_SUFFIX} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_SERVER_LIB_SUFFIX}
    PUBLIC
    BaSyx::Shared
    BaSyx::VAB
    lib::asio
)

add_library(basyx::server ALIAS ${BASYX_SERVER_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_SERVER_LIB_SUFFIX} ALIAS ${BASYX_SERVER_LIB_SUFFIX})

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_SERVER_LIB_SUFFIX} PROPERTIES FOLDER BaSyx)
endif()

if(BASYX_VERBOSE_CMAKE_OUTPUT)
	diagnostics_print(${BASYX_SERVER_LIB_SUFFIX})
endif()

build_source_group(${BASYX_SERVER_LIB_SUFFIX})

###############################################
###           Install section               ###
###############################################
if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_SERVER_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_SERVER_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_SERVER_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_SERVER_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_SERVER_LIBRARY_NAME}
)

install(EXPORT ${BASYX_SERVER_LIB_SUFFIX}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_SERVER_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_SERVER_LIBRARY_NAME}
)

install(TARGETS ${BASYX_SERVER_LIB_SUFFIX}
        EXPORT ${BASYX_SERVER_LIB_SUFFIX}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${BASYX_INCLUDE_DIR}/${PROJECT_SHORTNAME}/server"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_SHORTNAME}"
        FILES_MATCHING PATTERN "*.h"
)

endif()
