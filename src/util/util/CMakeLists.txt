
SET(SOURCE_FILES_UTIL
   ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
)

SET(HEADER_FILES_UTIL
)

target_sources(${BASYX_UTIL_LIB_SUFFIX}
   PRIVATE
   ${SOURCE_FILES_UTIL}
)

target_sources(${BASYX_UTIL_LIB_SUFFIX}
   INTERFACE
   ${HEADER_FILES_UTIL}
)

add_subdirectory(algorithm)
add_subdirectory(container)
add_subdirectory(optional)
add_subdirectory(string_view)
