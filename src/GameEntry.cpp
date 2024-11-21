#include <Audio.h>
#include <Camera.h>
#include <Core.h>
#include <Input.h>
#include <MainMenu.h>
#include <SceneGraph.h>
#include <Sprite.h>
#include <TweenEngine.h>

#include "Breakout.h"
#include "GlobalSettings.h"
#include "Resources.h"

void bin::Core::PreInit(bin::InitSettings& settings)
{
    settings.windowWidth = 1280;
    settings.windowHeight = 720;
    settings.windowTitle = "Breakout - By Julian Rijken";
}

void bin::Core::GameEntry()
{
    Audio::SetGlobalVolume(0.3f);

    Resources::LoadFont(bout::FontName::NES_Font, "Fonts/NES_Font.ttf", 8);

    Resources::LoadSound(bout::SoundName::WallHit, "Sounds/SFX 3.ogg");
    Resources::LoadSound(bout::SoundName::PaddleHit, "Sounds/Custom_PaddleHit.ogg");
    Resources::LoadSound(bout::SoundName::BrickBreak, "Sounds/Custom_BrickBreak.ogg");
    Resources::LoadSound(bout::SoundName::ButtonPress, "Sounds/Kenney_ButtonPress.ogg");
    Resources::LoadSound(bout::SoundName::ButtonRelease, "Sounds/Kenney_ButtonRelease.ogg");
    Resources::LoadSound(bout::SoundName::ButtonHover, "Sounds/SFX 13.ogg");
    Resources::LoadSound(bout::SoundName::GameStart, "Sounds/SFX 10.ogg");
    Resources::LoadSound(bout::SoundName::GameLost, "Sounds/SFX 11.ogg");
    Resources::LoadSound(bout::SoundName::GameWon, "Sounds/SFX 1.ogg");


    Input::AddInputAction(bout::InputActionName::FireBall, { { SDL_SCANCODE_SPACE }, true });
    Input::AddInputAction(bout::InputActionName::CheatForceRestart,
                               {
                                   {SDL_SCANCODE_R, SDL_SCANCODE_ESCAPE}
    });
    Input::AddInputAction(bout::InputActionName::CheatSpawnBall, { { SDL_SCANCODE_1 } });
    Input::AddInputAction(bout::InputActionName::CheatClearField, { { SDL_SCANCODE_2 } });

    SceneGraph::BindScene(bout::SceneName::Game, []() { bin::SceneGraph::AddNode<bout::Breakout>(); });

    SceneGraph::BindScene(bout::SceneName::MainMenu, []() { bin::SceneGraph::AddNode<bout::MainMenu>(); });

    SceneGraph::BindScene(bout::SceneName::GameWonScreen,
                               []()
                               {
                                   bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
                                   //
                               });

    SceneGraph::BindScene(bout::SceneName::GameLostScreen,
                               []()
                               {
                                   bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
                                   //
                               });


    SceneGraph::BindScene(bout::SceneName::TestingSceneGraph,
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
    Input::Bind(bout::InputActionName::CheatForceRestart,
                     [](const InputContext& context)
                     {
                         if(context.state != bin::ButtonState::Down)
                             return;

                         bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
                     });

    SceneGraph::LoadScene(bout::SceneName::MainMenu);
}
