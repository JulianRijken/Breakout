#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <Input.h>
#include <MainMenu.h>
#include <SceneGraph.h>
#include <Sprite.h>
#include <Tween.h>
#include <TweenEngine.h>

#include "Breakout.h"
#include "GlobalSettings.h"
#include "Resources.h"

void bin::Core::GameEntry()
{
    bin::Resources::LoadFont(bout::FontName::NES_Font, "Fonts/NES_Font.ttf", 8);
    bin::Input::AddInputAction(bout::InputActionName::FireBall, { { SDL_SCANCODE_SPACE }, true });
    bin::Input::AddInputAction(bout::InputActionName::ForceRestart, { { SDL_SCANCODE_R } });

    bin::SceneGraph::BindScene(bout::SceneName::Game, []() { bin::SceneGraph::AddNode<bout::Breakout>(); });

    bin::SceneGraph::BindScene(bout::SceneName::MainMenu, []() { bin::SceneGraph::AddNode<bout::MainMenu>(); });

    bin::SceneGraph::BindScene(bout::SceneName::Testing,
                               []()
                               {
                                   bin::SceneGraph::AddNode<Camera>();


                                   auto& spriteOne = bin::SceneGraph::AddNode<Sprite>();

                                   auto& spriteTwo = bin::SceneGraph::AddNode<Sprite>();
                                   spriteTwo.SetParent(&spriteOne);
                                   spriteTwo.SetLocalPosition({ 0, 4 });

                                   auto& spriteThree = bin::SceneGraph::AddNode<Sprite>();
                                   spriteThree.SetParent(&spriteTwo);
                                   spriteThree.SetLocalPosition({ 0, 4 });

                                   bin::TweenEngine::Start(
                                       bin::Tween{ .duration = 5.0f,
                                                   .onUpdate =
                                                       [&spriteOne, &spriteTwo](float value)
                                                   {
                                                       spriteOne.SetLocalPosition({ value, value });
                                                       spriteTwo.SetLocalPosition({ -value, value });
                                                   } },
                                       spriteOne);
                               });

    bin::SceneGraph::LoadScene(bout::SceneName::Game);
}
