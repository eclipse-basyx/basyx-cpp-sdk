#####################################################
###             tests_controlcomponent            ###
#####################################################

cmake_minimum_required(VERSION 3.1.0)

project(tests_controlcomponent)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
	test_ControlComponent.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} basyx::util basyx::shared lib::gtest basyx::vab tests::support basyx::controlcomponent tests::main)
gtest_discover_tests(${PROJECT_NAME})

diagnostics_print(${PROJECT_NAME})
