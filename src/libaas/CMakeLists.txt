########################################
###             libaas               ###
########################################

project(libaas)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.h)

add_library(libaas ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(libaas PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(libaas 
	PUBLIC 
		nlohmann_json::nlohmann_json
		spdlog::spdlog
		BaSyx::util
)

add_library(BaSyx::libaas ALIAS libaas)

build_source_group()