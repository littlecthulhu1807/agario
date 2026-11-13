include(FetchContent)

# --- SFML 3.1 (downloaded & built from source) ---
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TUTORIALS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.1.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(SFML)

# --- Client target ---
file(GLOB_RECURSE CLIENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(agario_client ${CLIENT_SOURCES})
target_link_libraries(agario_client PRIVATE
    SFML::Window
    SFML::Graphics
    SFML::Network
)
set_target_properties(agario_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/client/bin
)   