
SET(SOURCE_FILES_SERIALIZATION
)

SET(HEADER_FILES_SERIALIZATION
   ${CMAKE_CURRENT_SOURCE_DIR}/serializable_base.h
   ${CMAKE_CURRENT_SOURCE_DIR}/serializable.h
   ${CMAKE_CURRENT_SOURCE_DIR}/serializer.h
)

add_subdirectory(base)
add_subdirectory(json)
add_subdirectory(private)
add_subdirectory(xml)

###
target_sources(${BASYX_AAS_LIB_SHORTNAME}
   PRIVATE
   ${SOURCE_FILES_SERIALIZATION}
)

target_sources(${BASYX_AAS_LIB_SHORTNAME}
   PRIVATE
   ${HEADER_FILES_SERIALIZATION}
)
