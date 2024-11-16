#include "Core.h"

#include <fmt/core.h>
#include <fmt/format.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdexcept>

#include "GameTime.h"
#include "Renderer.h"
#include "SceneGraph.h"

jul::Core::Core()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
        throw std::runtime_error(fmt::format("SDL_Init Error: {}", SDL_GetError()));

    fmt::println("CPP Version {}", __cplusplus);


    // Not stored as member variable as SDL might change the width or height
    constexpr const char* windowTitle = "Julgen - Custom Engine by Julian Rijken";
    constexpr int windowWidth{ 1280 };
    constexpr int windowHeight{ 720 };

    m_WindowPtr = SDL_CreateWindow(windowTitle,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   windowWidth,
                                   windowHeight,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    Locator::Provide<Renderer>(m_WindowPtr);


    GameEntry();
    Run();
}


#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg) { static_cast<jul::Core*>(arg)->RunOneFrame(); }
#endif


void jul::Core::Run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#else

    while(not m_IsApplicationQuitting)
        RunOneFrame();
#endif
}

void jul::Core::RunOneFrame()
{
    GameTime::Increment();
    m_Lag += GameTime::GetDeltaTime();

    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent))
    {
        if(sdlEvent.type == SDL_QUIT)
            m_IsApplicationQuitting = true;

        // More input events
    }

    while(m_Lag >= jul::GameTime::GetFixedDeltaTime())
    {
        m_Lag -= jul::GameTime::GetFixedDeltaTime();

        jul::SceneGraph::GetInstance().FixedUpdate();
    }

    jul::SceneGraph::GetInstance().Update();
    Locator::Get<Renderer>().Render();
}

jul::Core::~Core()
{
    SDL_DestroyWindow(m_WindowPtr);
    m_WindowPtr = nullptr;
    SDL_Quit();
}
