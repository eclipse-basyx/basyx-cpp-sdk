
SET(SOURCE_FILES_BASE
   ${CMAKE_CURRENT_SOURCE_DIR}/basyx_enums.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/token.cpp
)

SET(HEADER_FILES_BASE
   ${CMAKE_CURRENT_SOURCE_DIR}/basyx_enum_base.h
   ${CMAKE_CURRENT_SOURCE_DIR}/copyable_base.h
   ${CMAKE_CURRENT_SOURCE_DIR}/copyable.h
   ${CMAKE_CURRENT_SOURCE_DIR}/elementcontainer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/elementvector.h
   ${CMAKE_CURRENT_SOURCE_DIR}/token.h
   ${CMAKE_CURRENT_SOURCE_DIR}/valuetypedefs.h
)

###
target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
   ${SOURCE_FILES_BASE}
)

target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
   ${HEADER_FILES_BASE}
)

