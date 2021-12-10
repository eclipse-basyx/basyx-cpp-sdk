########################################
###             libaas               ###
########################################

project(libaas)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.h)

add_library(aas ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(aas PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(aas
	PUBLIC 
		BaSyx::util
		nlohmann_json::nlohmann_json
		pugixml::pugixml
)

add_library(BaSyx::libaas ALIAS aas)

build_source_group()
