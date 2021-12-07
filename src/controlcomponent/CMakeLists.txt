######################################################
###              BaSyx::ControlComponent           ###
######################################################

include(CMakePackageConfigHelpers)

set (BASYX_CONTROLCOMPONENT_LIB_SUFFIX "Controlcomponent")

set (BASYX_CONTROLCOMPONENT_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_CONTROLCOMPONENT_LIB_SUFFIX}")

set (BASYX_CONTROLCOMPONENT_INCLUDE_DIR "${BASYX_INCLUDE_DIR}/BaSyx/controlcomponent")
set (PROJECT_INCLUDE_DIR BASYX_CONTROLCOMPONENT_INCLUDE_DIR)

add_library(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX})

set_target_properties(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} PROPERTIES SOVERSION ${BASYX_PACKAGE_VERSION_MAJOR})
set_target_properties(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}")
set_target_properties(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX}
	PUBLIC 
	    $<BUILD_INTERFACE:${BASYX_INCLUDE_DIR}>  
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)



#Implementation files
target_sources(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/enumerations/ControlComponentConstants.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/enumerations/ExecutionOrder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/enumerations/ExecutionState.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/map/ControlComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/simple/ControlComponent.cpp
)

#Header files
target_sources(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX}
    PRIVATE
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/interfaces/IControlComponentChangeListener.h
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/interfaces/IControlComponent.h

        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/enumerations/ControlComponentConstants.h
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/enumerations/ExecutionMode.h
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/enumerations/ExecutionOrder.h
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/enumerations/ExecutionState.h
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/enumerations/OccupationState.h

        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/map/ControlComponent.h
        ${BASYX_CONTROLCOMPONENT_INCLUDE_DIR}/simple/ControlComponent.h
        )

add_library(basyx::controlcomponent ALIAS ${BASYX_CONTROLCOMPONENT_LIB_SUFFIX})
add_library(${PROJECT_SHORTNAME}::${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} ALIAS ${BASYX_CONTROLCOMPONENT_LIB_SUFFIX})

target_include_directories(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX}
        PUBLIC
        BaSyx::Shared
        BaSyx::VAB
)

if(BASYX_IS_SUBMODULE)
	set_target_properties(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX} PROPERTIES FOLDER BaSyx)
endif()

build_source_group(${BASYX_CONTROLCOMPONENT_LIB_SUFFIX})
