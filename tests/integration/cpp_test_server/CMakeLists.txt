add_executable(cpp_test_server cpp_test_server.cpp) 
target_link_libraries(cpp_test_server basyx::shared basyx::log basyx::vab basyx::abstraction basyx::server tests::support)