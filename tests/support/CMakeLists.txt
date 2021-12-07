###############################################
###              tests_support              ###
###############################################

cmake_minimum_required(VERSION 3.1.0)
project(tests)

add_library(tests_support)

target_sources(tests_support
    PRIVATE
        macros.h
        vab/stub/elements/SimpleVABElement.cpp
        vab/stub/elements/SimpleVABElement.h
)

target_include_directories(tests_support PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(tests_support basyx::util basyx::vab basyx::shared lib::gtest)
add_library(tests::support ALIAS tests_support)

diagnostics_print(tests_support)
