
SET(SOURCE_FILES_BASYX
   ${CMAKE_CURRENT_SOURCE_DIR}/administrative_information.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/assetadministrationshell.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/environment.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/haskind.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/hassemantics.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/identifiable.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/identifier.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/identifierkeyvaluepair.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/key.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/langstringset.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/modeltype.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/qualifiable.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/referable.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/reference.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/submodel.cpp
)

SET(HEADER_FILES_BASYX
   ${CMAKE_CURRENT_SOURCE_DIR}/administrative_information.h
   ${CMAKE_CURRENT_SOURCE_DIR}/assetadministrationshell.h
   ${CMAKE_CURRENT_SOURCE_DIR}/environment.h
   ${CMAKE_CURRENT_SOURCE_DIR}/haskind.h
   ${CMAKE_CURRENT_SOURCE_DIR}/hassemantics.h
   ${CMAKE_CURRENT_SOURCE_DIR}/identifiable.h
   ${CMAKE_CURRENT_SOURCE_DIR}/identifier.h
   ${CMAKE_CURRENT_SOURCE_DIR}/identifierkeyvaluepair.h
   ${CMAKE_CURRENT_SOURCE_DIR}/key.h
   ${CMAKE_CURRENT_SOURCE_DIR}/langstringset.h
   ${CMAKE_CURRENT_SOURCE_DIR}/modeltype.h
   ${CMAKE_CURRENT_SOURCE_DIR}/qualifiable.h
   ${CMAKE_CURRENT_SOURCE_DIR}/referable.h
   ${CMAKE_CURRENT_SOURCE_DIR}/reference.h
   ${CMAKE_CURRENT_SOURCE_DIR}/submodel.h
)

target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
   ${SOURCE_FILES_BASYX}
)

target_sources(${BASYX_AAS_LIB_SUFFIX}
   PRIVATE
   ${HEADER_FILES_BASYX}
)

add_subdirectory(asset)
add_subdirectory(base)
add_subdirectory(constraints)
add_subdirectory(dataspecification)
add_subdirectory(enums)
add_subdirectory(semantics)
add_subdirectory(serialization)
add_subdirectory(submodelelement)
