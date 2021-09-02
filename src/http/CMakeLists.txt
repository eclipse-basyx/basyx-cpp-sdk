########################################
###             basyxpp-http         ###
########################################

project(basyxpp-http)

set(SOURCE_FILES 
	basyxpp-http/httpHandler.cpp
)

set(HEADER_FILES 
	basyxpp-http/httpHandler.h
	basyxpp-http/httplib/httplib.h
)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		spdlog::spdlog
		BaSyx::libaas
		BaSyx::util
)

add_library(BaSyx::http ALIAS basyxpp-http)

add_executable(basyxpp-http-exe basyxpp-http/main.cpp)
target_link_libraries(basyxpp-http-exe
	PUBLIC
		spdlog::spdlog
		BaSyx::http
		BaSyx::libaas
		BaSyx::util
	)

if(${BASYX_BUILD_TESTS})
	add_subdirectory(basyxpp-http-tests)
endif()

build_source_group()
