#include "Core.h"

#include "Audio.h"

#define SDL_MAIN_HANDLED
#include <fmt/core.h>
#include <fmt/format.h>
#include <SDL.h>

#include <stdexcept>

#include "GameTime.h"
#include "Input.h"
#include "MessageQueue.h"
#include "Physics.h"
#include "Renderer.h"
#include "Resources.h"
#include "SceneGraph.h"
#include "TweenEngine.h"

bin::Core::Core()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(fmt::format("SDL_Init Error: {}", SDL_GetError()));

    // Not stored as member variable as SDL might change the width or height
    constexpr const char* windowTitle = "Breakout - By Julian Rijken";
    constexpr int windowWidth{ 1280 };
    constexpr int windowHeight{ 720 };

    m_WindowPtr = SDL_CreateWindow(
        windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);

    Locator::Provide<Renderer>(m_WindowPtr);
    Locator::Provide<Physics>();
    Locator::Provide<Audio>();

    Resources::Initialize();

    GameEntry();
    Run();
}


#ifdef __EMSCRIPTEN__
#include "emscripten.h"
void LoopCallback(void* arg) { static_cast<bin::Core*>(arg)->IncrementFrame(); }
#endif


void bin::Core::Run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#else

    while(not m_IsApplicationQuitting)
        IncrementFrame();
#endif
}

void bin::Core::IncrementFrame()
{
    // Game Time
    GameTime::IncrementFrame();
    m_Lag += GameTime::GetDeltaTime();

    // Cleanup SceneGraph
    SceneGraph::GetInstance().CleanupNodesSetToDestroy();
    // Load Scene set to load for next frame
    SceneGraph::GetInstance().ActivateSceneSetToLoad();
    // Move added nodes
    SceneGraph::GetInstance().MoveAddedNodesToActiveNodes();

    // Input
    Input::GetInstance().ProcessInput(m_IsApplicationQuitting);

    // Fixed Update Loop
    while(m_Lag >= GameTime::GetFixedDeltaTime())
    {
        m_Lag -= GameTime::GetFixedDeltaTime();
        SceneGraph::GetInstance().FixedUpdateAll();
    }

    // Update Scene Graph
    SceneGraph::GetInstance().UpdateAll();

    // Message Dispatch
    MessageQueue::Dispatch();

    // Update Tweens
    TweenEngine::Update();

    // Late Update Scene Graph
    SceneGraph::GetInstance().LateUpdateAll();

    // Render
    Locator::Get<Renderer>().Render();
}

bin::Core::~Core()
{
    SceneGraph::GetInstance().ClearScene();

    Resources::Cleanup();
    Locator::Release<Audio>();
    Locator::Release<Renderer>();
    Locator::Release<Physics>();

    SDL_DestroyWindow(m_WindowPtr);
    SDL_Quit();
}
