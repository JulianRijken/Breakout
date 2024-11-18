#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <Input.h>
#include <MainMenu.h>
#include <SceneGraph.h>

#include "Breakout.h"
#include "GlobalSettings.h"
#include "Resources.h"

void bin::Core::GameEntry()
{
    bin::Resources::LoadFont(0, "Fonts/NES_Font.ttf", 8);
    bin::Input::AddInputAction(bout::InputActionName::FireBall, { { SDL_SCANCODE_SPACE }, true });
    bin::Input::AddInputAction(bout::InputActionName::ForceRestart, { { SDL_SCANCODE_R } });

    bin::SceneGraph::BindScene(bout::SceneName::Game, []() { bin::SceneGraph::AddNode<bout::Breakout>(); });

    bin::SceneGraph::BindScene(bout::SceneName::MainMenu, []() { bin::SceneGraph::AddNode<bout::MainMenu>(); });

    bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
}
