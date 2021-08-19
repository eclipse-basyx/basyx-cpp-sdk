###############################################
###              BaSyx C++ SDK  2.0         ###
###############################################
cmake_minimum_required(VERSION 3.13.0)

set(PROJECT_NAME "BaSyx C++ SDK 2.0")
set(PROJECT_SHORTNAME "BaSyxCpp")

project(${PROJECT_NAME} VERSION "2.0")

### CMake settings ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(build_source_group)
include(diagnostics_print)
include(enable_clang_format)
include(enable_clang_tidy)
include(enable_cppcheck)
include(FetchContent)

# Check if standalone build or being included as submodule
get_directory_property(BASYX_IS_SUBMODULE PARENT_DIRECTORY)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### Project settings ###
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "" )

if(NOT BASYX_IS_SUBMODULE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

### BaSyx directories ###
set(BASYX_SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BASYX_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(BASYX_TEST_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/tests")

### Build options ###
set(BASYX_BUILD_TESTS ${BASYX_BUILD_TESTS_DEFAULT} CACHE BOOL "Build unit tests")
option(BASYX_VERBOSE_CMAKE_OUTPUT "Show detailed CMake output" ON)

### Compiler settings ###
set(CMAKE_CXX_STANDARD 17)

###############################################
###           Library Settings              ###
###############################################

### Detect OS threading library ###
find_package(Threads)

### spdlog ###
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.x
)

FetchContent_GetProperties(spdlog)
if (NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

### nlohmann-json ###
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

### GoogleTest ###
if(${BASYX_BUILD_TESTS})
    include(GoogleTest)

    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()


###############################################
###           Library Directory             ###
###############################################

#add_subdirectory(lib/json)

###############################################
###           Source Directory              ###
###############################################

add_subdirectory(src/util)
add_subdirectory(src/libaas)
add_subdirectory(src/http)
add_subdirectory(src/cli)

###############################################
###           Test Directory                ###
###############################################

if(${BASYX_BUILD_TESTS})
    include( CTest )
    add_subdirectory(tests/tests_libaas)
    add_subdirectory(tests/tests_misc)
endif()

###############################################
###           Utility Projects              ###
###############################################

if(${BASYX_UTILITY_PROJECTS})
    enable_clang_format()
    enable_clang_tidy()
    enable_cppcheck()
endif()
