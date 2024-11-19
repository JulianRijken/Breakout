cmake_minimum_required(VERSION 3.18)
project(Breakout)

add_subdirectory(Breakin)


set(TARGET_NAME Breakout)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

option(USE_ASAN "Use ASAN" FALSE)


# Adds the source files to the executible
set(SOURCE_FILES
    ${SOURCE_DIR}/Breakout.h        ${SOURCE_DIR}/Breakout.cpp
    ${SOURCE_DIR}/Paddle.h          ${SOURCE_DIR}/Paddle.cpp
                                    ${SOURCE_DIR}/GameEntry.cpp
    ${SOURCE_DIR}/Ball.h            ${SOURCE_DIR}/Ball.cpp
    ${SOURCE_DIR}/Playfield.h       ${SOURCE_DIR}/Playfield.cpp
    ${SOURCE_DIR}/Brick.h           ${SOURCE_DIR}/Brick.cpp
    ${SOURCE_DIR}/Trail.h           ${SOURCE_DIR}/Trail.cpp
    ${SOURCE_DIR}/HUD.h             ${SOURCE_DIR}/HUD.cpp
    ${SOURCE_DIR}/Prefabs.h         ${SOURCE_DIR}/Prefabs.cpp
    ${SOURCE_DIR}/HUD.h             ${SOURCE_DIR}/HUD.cpp
    ${SOURCE_DIR}/GameStats.h       ${SOURCE_DIR}/GameStats.cpp
    ${SOURCE_DIR}/MainMenu.h        ${SOURCE_DIR}/MainMenu.cpp
    ${SOURCE_DIR}/GlobalSettings.h  ${SOURCE_DIR}/GlobalSettings.cpp
    ${SOURCE_DIR}/Wall.h            ${SOURCE_DIR}/Wall.cpp
)

add_executable(${TARGET_NAME}
    ${SOURCE_FILES}
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${SOURCE_DIR}
)

if(USE_ASAN)
    if(WIN32)
        target_compile_options(${TARGET_NAME} PUBLIC /fsanitize=address)
        target_link_options(${TARGET_NAME} PUBLIC /fsanitize=address)
    else()
        target_compile_options(${TARGET_NAME} PUBLIC -fsanitize=address)
        target_link_options(${TARGET_NAME} PUBLIC -fsanitize=address)
    endif()
endif()


# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
set_property(TARGET ${TARGET_NAME} PROPERTY
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /MP>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# Visual studio needs to be special
if(WIN32)
    # Fix startup project for visual stuidio
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
    # Fix working directory for visual studio
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
endif()

target_link_libraries(${TARGET_NAME} PRIVATE Breakin)
