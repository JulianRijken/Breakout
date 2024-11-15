#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdexcept>

jul::Game::Game()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

    // Not stored as member variable as SDL might change the width
    constexpr const char* windowTitle = "Julgen - Custom Engine by Julian Rijken";
    constexpr int windowWidth{ 1280 };
    constexpr int windowHeight{ 720 };

    m_Window = SDL_CreateWindow(windowTitle,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                windowWidth,
                                windowHeight,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    Run();
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg) { static_cast<jul::Game*>(arg)->RunOneFrame(); }
#endif


void jul::Game::Run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#else

    while(not m_IsApplicationQuitting)
        RunOneFrame();
#endif
}

void jul::Game::RunOneFrame()
{
    SDL_Event sdlEvent;

    while(SDL_PollEvent(&sdlEvent))
    {
        if(sdlEvent.type == SDL_QUIT)
            m_IsApplicationQuitting = true;

        //
    }
}

jul::Game::~Game()
{
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    SDL_Quit();
}
