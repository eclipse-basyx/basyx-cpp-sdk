
SET(SOURCE_FILES_UTIL
   ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
)

SET(HEADER_FILES_UTIL
   ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/string.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/container/container.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/optional/optional.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/string_view/basic_string_view.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/string_view/string_view.hpp
)

target_sources(${BASYX_UTIL_LIB_SHORTNAME}
   PRIVATE
   ${SOURCE_FILES_UTIL}
)

target_sources(${BASYX_UTIL_LIB_SHORTNAME}
   PRIVATE
   ${HEADER_FILES_UTIL}
)
