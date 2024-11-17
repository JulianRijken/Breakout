#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <Input.h>
#include <SceneGraph.h>

#include "Breakout.h"
#include "Resources.h"


void bin::Core::GameEntry()
{
    bin::Resources::LoadFont(0, "Fonts/NES_Font.ttf", 8);
    bin::Input::GetInstance().AddInputAction(bout::InputActionName::FireBall, { { SDL_SCANCODE_SPACE }, {} });
    bin::Input::GetInstance().AddInputAction(bout::InputActionName::ForceRestart, { { SDL_SCANCODE_R }, {} });

    bin::SceneGraph::BindScene(bout::SceneName::Game,
                               []()
                               {
                                   // Game Scene
                                   bin::SceneGraph::AddNode<bout::Breakout>();
                               });

    bin::SceneGraph::LoadScene(bout::SceneName::Game);
}
