add_executable(cpp_test_connector cpp_test_connector.cpp)
target_link_libraries(cpp_test_connector basyx::shared basyx::log basyx::vab tests::support)
