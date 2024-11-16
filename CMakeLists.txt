cmake_minimum_required(VERSION 3.18)
project(Breakout)


set(TARGET_NAME Breakout)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Append cmake libraries file
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(Libraries)


# Use Libraries file and fetch / find all needed libs
make_libs_available()


# Adds the source files to the executible
set(SOURCE_FILES
                              ${SOURCE_DIR}/Main.cpp
    ${SOURCE_DIR}/Core.h      ${SOURCE_DIR}/Core.cpp
    ${SOURCE_DIR}/GameTime.h  ${SOURCE_DIR}/GameTime.cpp
    ${SOURCE_DIR}/Renderer.h  ${SOURCE_DIR}/Renderer.cpp
    ${SOURCE_DIR}/Breakout.h  ${SOURCE_DIR}/Breakout.cpp
    ${SOURCE_DIR}/Locator.h
    ${SOURCE_DIR}/MathExtensions.h
)

add_executable(${TARGET_NAME}
    ${SOURCE_FILES}

)


# Include source directories
target_include_directories(${TARGET_NAME} PUBLIC
    ${SOURCE_DIR}
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
        # "--preload-file ${CMAKE_SOURCE_DIR}/Assets@Assets"
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
