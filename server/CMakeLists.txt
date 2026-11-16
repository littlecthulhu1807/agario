set(BOOST_INCLUDE_LIBRARIES asio)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.gz
)
FetchContent_MakeAvailable(Boost) 

# --- Server target ---
file(GLOB_RECURSE SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(agario_server ${SERVER_SOURCES})
target_link_libraries(agario_server PRIVATE Boost::asio)  
set_target_properties(agario_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/server/bin
)   