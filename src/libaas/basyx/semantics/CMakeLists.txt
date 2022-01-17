
SET(SOURCE_FILES_SEMANTICS
   ${CMAKE_CURRENT_SOURCE_DIR}/conceptdescription.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/hasdataspecification.cpp

)

SET(HEADER_FILES_SEMANTICS
   ${CMAKE_CURRENT_SOURCE_DIR}/conceptdescription.h
   ${CMAKE_CURRENT_SOURCE_DIR}/hasdataspecification.h
)

###
target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
   ${SOURCE_FILES_SEMANTICS}
)

target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
   ${HEADER_FILES_SEMANTICS}
)
