###############################################
###              ASIO                       ###
###############################################

cmake_minimum_required(VERSION 2.8.4)

# Allow versioning the subproject
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

# Version from ./asio/version.hpp
set(ASIO_VERSION_MAJOR 1)
set(ASIO_VERSION_MINOR 12)
set(ASIO_VERSION_PATCH 2)

project(asio
        VERSION ${ASIO_VERSION_MAJOR}.${ASIO_VERSION_MINOR}.${ASIO_VERSION_PATCH}
)

add_library(asio INTERFACE)
#target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(asio INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
add_library(lib::asio ALIAS asio)

install(EXPORT asio DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaSyxAsio)

install(TARGETS asio
        EXPORT asio
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Trailing slash to install directly to $include and not $include/asio
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        PATTERN "CMakeFiles" EXCLUDE
        PATTERN "Makefile" EXCLUDE
        PATTERN "CMakeLists.txt" EXCLUDE
        PATTERN "cmake_install.cmake" EXCLUDE
        PATTERN "asio/*"
)
