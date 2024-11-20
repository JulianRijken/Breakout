function(make_libs_available)

    set(FETCHCONTENT_QUIET OFF)

    include(FetchContent)


    if(WIN32 OR EMSCRIPTEN)

        message(STATUS "Downloading " glm...)
        FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm
            GIT_TAG 1.0.1
            GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(glm)


        message(STATUS "Downloading " fmt...)
        FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 10.2.1
            GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(fmt)


        if(WIN32) # EMSCRIPTEN Handles SDL
            message(STATUS "Downloading " sdl2...)
            set(SDL_STATIC OFF)
            FetchContent_Declare(
                sdl2
                GIT_REPOSITORY https://github.com/libsdl-org/SDL
                GIT_TAG release-2.30.9
                GIT_SHALLOW TRUE
                OVERRIDE_FIND_PACKAGE TRUE)
            FetchContent_MakeAvailable(sdl2)



            set(SDL2TTF_VENDORED ON)  # Windows requires building FreeType
            message(STATUS "Downloading " sdl2_ttf...)
            FetchContent_Declare(
                sdl2-ttf
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
                GIT_TAG release-2.22.0
                GIT_SHALLOW TRUE
                OVERRIDE_FIND_PACKAGE TRUE)
            FetchContent_MakeAvailable(sdl2-ttf)



            set(SDL2IMAGE_BMP OFF)
            set(SDL2IMAGE_GIF OFF)
            set(SDL2IMAGE_JPG OFF)
            set(SDL2IMAGE_JXL OFF)
            set(SDL2IMAGE_PNG ON)
            set(SDL2IMAGE_VENDORED ON)
            message(STATUS "Downloading " sdl2_image...)
            FetchContent_Declare(
                sdl2-image
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
                GIT_TAG release-2.8.2
                GIT_SHALLOW TRUE
                OVERRIDE_FIND_PACKAGE TRUE)
            FetchContent_MakeAvailable(sdl2-image)

            message(STATUS "Downloading " sdl2_mixer...)
            FetchContent_Declare(
                sdl2-mixer
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
                GIT_TAG release-2.8.0
                GIT_SHALLOW TRUE
                OVERRIDE_FIND_PACKAGE TRUE)
            set(SDL_MIXER_ENABLE_OPUS OFF CACHE BOOL "Disable Opus codec")
            set(SDL_MIXER_ENABLE_MP3 ON CACHE BOOL "Enable MP3 codec")
            set(SDL_MIXER_ENABLE_VORBIS ON CACHE BOOL "Enable Ogg Vorbis codec")
            set(SDL_MIXER_ENABLE_FLAC ON CACHE BOOL "Enable FLAC codec")

            FetchContent_MakeAvailable(sdl2-mixer)

        endif()

    else()
        find_package(glm REQUIRED)
        find_package(fmt REQUIRED)

        find_package(SDL2 REQUIRED)
        find_package(SDL2_ttf REQUIRED)
        find_package(SDL2_image REQUIRED)
        find_package(SDL2_mixer REQUIRED)
    endif()
endfunction()
