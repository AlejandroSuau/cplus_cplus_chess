CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT(ChessGame)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

include(FetchContent)

# Fetch SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.3 # O la versión que prefieras
)
FetchContent_MakeAvailable(SDL2)

# Fetch SDL2_image
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
)
FetchContent_MakeAvailable(SDL2_image)

# Fetch SDL2_mixer
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.0
)
### Otherwise you can install those.
set(SDL2MIXER_VENDORED ON)
set(SDL2MIXER_OPUS OFF)
FetchContent_MakeAvailable(SDL2_mixer)

# Fetch SDL2_ttf
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
)
FetchContent_MakeAvailable(SDL2_ttf)

# Fetch nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# Source files
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/code")
file(GLOB_RECURSE MODULES_SOURCES ${SOURCE_DIR}/*.cppm ${SOURCE_DIR}/*.cpp)
set(SOURCES ${MODULES_SOURCES} "${CMAKE_SOURCE_DIR}/main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/code
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    nlohmann_json::nlohmann_json
)

# macOS specific frameworks
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
    "-framework CoreVideo"
    "-framework AudioToolbox"
    "-framework CoreAudio"
    "-framework AVFoundation"
    "-framework GameController"
    "-framework Metal"
    "-framework Foundation"
    "-framework ForceFeedback"
    "-framework CoreHaptics"
    "-framework Carbon"
)
endif()

# Assets (copy to build directory)
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "${CMAKE_BINARY_DIR}/assets")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
)

message(STATUS "C++ standard set to: ${CMAKE_CXX_STANDARD}")