include(FetchContent)
find_package(Threads REQUIRED)

# --- Standalone Asio (header-only, downloaded) ---
FetchContent_Declare(
    asio
    GIT_REPOSITORY  https://github.com/chriskohlhoff/asio.git
    GIT_TAG         asio-1-38-2
    GIT_SHALLOW     TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
)
FetchContent_MakeAvailable(asio)

add_library(asio_iface INTERFACE)
target_include_directories(asio_iface INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(asio_iface INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)
target_link_libraries(asio_iface INTERFACE Threads::Threads)

# --- Server target ---
file(GLOB_RECURSE SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(agario_server ${SERVER_SOURCES})
target_link_libraries(agario_server PRIVATE asio_iface)
set_target_properties(agario_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/server/bin
)   