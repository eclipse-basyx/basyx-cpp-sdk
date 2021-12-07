###############################################
###              tests_vab                  ###
###############################################

cmake_minimum_required(VERSION 3.1.0)
project(tests_vab)

add_executable(tests_vab)

target_sources(tests_vab
    PRIVATE
        core/proxy/test_vab_elementproxy.cpp
        provider/basyx/frame/test_BaSyxNativeFrameProcessor.cpp
        provider/basyx/frame/test_BaSyxNativeFrame.cpp
        provider/basyx/test_BaSyxNative.cpp
        provider/test_hashmap.cpp
        provider/test_hashmap_collection.cpp
        provider/test_hashmap_map.cpp
        snippet/MapCreateDelete.h
        snippet/MapInvoke.h
        snippet/MapRead.h
        snippet/MapUpdate.h
		snippet/TestCollectionProperty.h
		path/test_VABPath.cpp
        support/MockupModelProvider.h
)

target_include_directories(tests_vab PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(tests_vab basyx::util basyx::vab basyx::shared lib::gtest tests::support tests::main basyx::server)
#temporarily disabled# gtest_discover_tests(tests_vab)

diagnostics_print(tests_vab)
