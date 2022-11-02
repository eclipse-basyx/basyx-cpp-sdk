###############################################
###              Tests                      ###
###############################################

cmake_minimum_required(VERSION 2.8.4...3.13)

# Allow versioning the subproject
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project(tests
        VERSION ${BASYX_PACKAGE_VERSION_MAJOR}.${BASYX_PACKAGE_VERSION_MINOR}.${BASYX_PACKAGE_VERSION_PATCH}
)

### tests::main ###

add_library(tests_main support/main.cpp)
target_link_libraries(tests_main gtest)
add_library(tests::main ALIAS tests_main)
diagnostics_print(tests_main)

### Unit Tests ###

add_subdirectory(regression/util)
add_subdirectory(regression/vab)
add_subdirectory(regression/submodel)
add_subdirectory(regression/controlcomponent)

if(${BASYX_MODULE_OPCUA})
    add_subdirectory(regression/opcua)
endif()

### Integration tests ###

if(BASYX_BUILD_INTEGRATION_TESTS)
	add_subdirectory(integration)
endif()

### Support ###

add_subdirectory(support)

