cmake_minimum_required(VERSION 3.13.0)

set(CPPBASE64_VERSION_MAJOR 2)
set(CPPBASE64_VERSION_MINOR 8)

project(cppbase64 VERSION ${CPPBASE64_VERSION_MAJOR}.${CPPBASE64_VERSION_MAJOR})

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(cppbase64 ${SOURCE_FILES})

target_include_directories(cppbase64
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS cppbase64
        EXPORT cppbase64-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT cppbase64-targets
        FILE cppbase64-targets.cmake
        NAMESPACE cppbase64::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cppbase64
)

add_library(cppbase64::cppbase64 ALIAS cppbase64)
build_source_group(cppbase64)
diagnostics_print(cppbase64)
