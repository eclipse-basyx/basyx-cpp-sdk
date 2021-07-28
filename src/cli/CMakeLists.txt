########################################
###                CLI               ###
########################################

project(cli)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.h)

add_executable(basyx_cli ${SOURCE_FILES})
target_link_libraries(basyx_cli PRIVATE BaSyx::libaas)

build_source_group()