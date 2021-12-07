
find_path(ASIO_INCLUDE asio.hpp
    HINTS
    "/usr/include"
    "/usr/local/include"
    "/opt/local/include"
    "/opt/include"
)

if(ASIO_INCLUDE)
add_library(asio INTERFACE IMPORTED GLOBAL)
target_include_directories(asio INTERFACE ${ASIO_INCLUDE})
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
add_library(lib::asio ALIAS asio)
add_library(asio::asio ALIAS asio)
message(STATUS "Found asio include at: ${ASIO_INCLUDE}")
else()
    message(FATAL_ERROR "Failed to locate ASIO dependency.")
endif()
