###############################################
###              GTest                      ###
###############################################

cmake_minimum_required(VERSION 2.8.4...3.13)

# Allow versioning the subproject
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

# Version from gtest Release page: https://github.com/google/googletest/releases
set(GTEST_VERSION_MAJOR 1)
set(GTEST_VERSION_MINOR 8)
set(GTEST_VERSION_PATCH 1)

project(gtest
        VERSION ${GTEST_VERSION_MAJOR}.${GTEST_VERSION_MINOR}.${GTEST_VERSION_PATCH}
)

###''' SOURCE AND HEADER FILES '''###

file(GLOB_RECURSE SOURCE_FILES *.cc)
file(GLOB_RECURSE HEADER_FILES *.h)

### GTest ###

add_library(gtest ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(gtest PUBLIC ${PROJECT_SOURCE_DIR}) 
target_link_libraries(gtest Threads::Threads)
add_library(lib::gtest ALIAS gtest)

diagnostics_print(gtest)
