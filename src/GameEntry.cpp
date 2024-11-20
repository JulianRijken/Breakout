#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <Input.h>
#include <MainMenu.h>
#include <SceneGraph.h>
#include <Sprite.h>
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
                                   spriteTwo.SetLocalPosition({ 0, 2 });

                                   auto& spriteThree = bin::SceneGraph::AddNode<Sprite>();
                                   spriteThree.SetParent(&spriteTwo);
                                   spriteThree.SetLocalPosition({ -5, 5 });

                                   spriteThree.SetWorldAngle(0.0f);
                                   spriteThree.SetWorldPosition({ -5, 5 });
                                   spriteThree.SetWorldScale({ 1, 1 });

                                   spriteThree.m_UseAbsoluteAngle = true;


                                   bin::TweenEngine::Start({ .duration = 2.0f,
                                                             .onUpdate =
                                                                 [&spriteOne, &spriteTwo](float value)
                                                             {
                                                                 spriteOne.SetLocalScale({ 1.0f, value * 2 });
                                                                 spriteOne.SetLocalPosition({ value, value });
                                                                 spriteOne.SetLocalAngle(value * 360.0f);
                                                                 spriteTwo.SetLocalPosition({ -value * 2, -value * 2 });
                                                                 spriteTwo.SetLocalAngle(value * 180.0f);

                                                                 // spriteThree.SetWorldAngle(0.0f);
                                                                 // spriteThree.SetWorldPosition({ -5, 5 });
                                                                 // spriteThree.SetWorldScale({ 1, 1 });
                                                             } },
                                                           spriteOne);
                               });

    // Make sure the user can always restart
    bin::Input::Bind(bout::InputActionName::ForceRestart,
                     [](const InputContext& context)
                     {
                         if(context.state != bin::ButtonState::Down)
                             return;

                         bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
                     });

    bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
}
