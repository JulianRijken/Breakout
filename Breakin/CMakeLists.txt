cmake_minimum_required(VERSION 3.18)
project(Breakin)


set(TARGET_NAME Breakin)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Append cmake libraries file
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(Libraries)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Use Libraries file and fetch / find all needed libs
make_libs_available()


# Adds the source files to the executible
set(BREAKIN_SOURCE_FILES

    # Core
                                                ${SOURCE_DIR}/Core/Main.cpp
    ${SOURCE_DIR}/Core/Core.h                   ${SOURCE_DIR}/Core/Core.cpp

    # Engine
    ${SOURCE_DIR}/Engine/GameTime.h             ${SOURCE_DIR}/Engine/GameTime.cpp
    ${SOURCE_DIR}/Engine/Renderer.h             ${SOURCE_DIR}/Engine/Renderer.cpp
    ${SOURCE_DIR}/Engine/Physics.h              ${SOURCE_DIR}/Engine/Physics.cpp
    ${SOURCE_DIR}/Engine/SceneGraph.h           ${SOURCE_DIR}/Engine/SceneGraph.cpp
    ${SOURCE_DIR}/Engine/Input.h                ${SOURCE_DIR}/Engine/Input.cpp

    # Resources
    ${SOURCE_DIR}/Engine/Resources/Font.h       ${SOURCE_DIR}/Engine/Resources/Font.cpp
    ${SOURCE_DIR}/Engine/Resources/Texture.h    ${SOURCE_DIR}/Engine/Resources/Texture.cpp
    ${SOURCE_DIR}/Engine/Resources/Resources.h  ${SOURCE_DIR}/Engine/Resources/Resources.cpp

    # Nodes
    ${SOURCE_DIR}/Nodes/Node.h                  ${SOURCE_DIR}/Nodes/Node.cpp
    ${SOURCE_DIR}/Nodes/BoxCollider.h           ${SOURCE_DIR}/Nodes/BoxCollider.cpp
    ${SOURCE_DIR}/Nodes/Camera.h                ${SOURCE_DIR}/Nodes/Camera.cpp
    ${SOURCE_DIR}/Nodes/Text.h                  ${SOURCE_DIR}/Nodes/Text.cpp
    ${SOURCE_DIR}/Nodes/Button.h                ${SOURCE_DIR}/Nodes/Button.cpp
    ${SOURCE_DIR}/Nodes/Sprite.h                ${SOURCE_DIR}/Nodes/Sprite.cpp

    # Helper
    ${SOURCE_DIR}/Helper/Event.h
    ${SOURCE_DIR}/Helper/Locator.h
    ${SOURCE_DIR}/Helper/MathExtensions.h
    ${SOURCE_DIR}/Helper/MessageQueue.h         ${SOURCE_DIR}/Helper/MessageQueue.cpp
    ${SOURCE_DIR}/Helper/Singleton.h


    # Tween
    ${SOURCE_DIR}/Tween/EaseFinction.h          ${SOURCE_DIR}/Tween/EaseFinction.cpp
    ${SOURCE_DIR}/Tween/TweenEngine.h           ${SOURCE_DIR}/Tween/TweenEngine.cpp
    ${SOURCE_DIR}/Tween/TweenInstance.h         ${SOURCE_DIR}/Tween/TweenInstance.cpp
)

add_library(${TARGET_NAME} STATIC
    ${BREAKIN_SOURCE_FILES}
)


# Include source directories
target_include_directories(${TARGET_NAME} PUBLIC
    ${SOURCE_DIR}
    ${SOURCE_DIR}/Core
    ${SOURCE_DIR}/Nodes
    ${SOURCE_DIR}/Engine
    ${SOURCE_DIR}/Engine/Resources
    ${SOURCE_DIR}/Helper
    ${SOURCE_DIR}/Tween
)

target_link_libraries(${TARGET_NAME} PUBLIC
    glm::glm
    fmt::fmt
)

if(EMSCRIPTEN)
    target_compile_options(${TARGET_NAME} PUBLIC -pthread -gsource-map -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g -Wno-switch)
    target_link_libraries(${TARGET_NAME} PUBLIC -sERROR_ON_UNDEFINED_SYMBOLS=0 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2)

    SET(CMAKE_EXECUTABLE_SUFFIX ".html")

    target_link_libraries(${TARGET_NAME} PUBLIC
        "--preload-file ${CMAKE_SOURCE_DIR}/Assets@Assets"
        "-s ALLOW_MEMORY_GROWTH"
        "-s EXIT_RUNTIME=1"
        "-s SDL2_IMAGE_FORMATS='[\"png\"]'"
        "-s ASSERTIONS"
        "-s GL_DEBUG"
        "-s DEMANGLE_SUPPORT=1"
        "-s OFFSCREEN_FRAMEBUFFER=1"
        "--shell-file \"${EMSCRIPTEN_ROOT_PATH}/src/shell_minimal.html\""
    )
else()
    target_link_libraries(${TARGET_NAME} PUBLIC
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf
        SDL2_image::SDL2_image
    )
endif()


target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
set_property(TARGET ${TARGET_NAME} PROPERTY
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /MP> # MSVC
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# Visual studio needs to be special
if(WIN32)
    # Fix startup project for visual stuidio
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
    # Fix working directory for visual studio
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
endif()

if(NOT EMSCRIPTEN)
    # Make sure the asset folder get's copyed or linked correctly
    if(WIN32)
        set(SYMLINK_COMMAND copy_directory)
    else()
        set(SYMLINK_COMMAND create_symlink)
    endif()

    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E ${SYMLINK_COMMAND}
                    "${CMAKE_SOURCE_DIR}/Assets"
                    "${CMAKE_BINARY_DIR}/Assets")
endif()
