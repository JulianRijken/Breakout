#include <Audio.h>
#include <Camera.h>
#include <Core.h>
#include <Input.h>
#include <MainMenu.h>
#include <SceneGraph.h>
#include <Sprite.h>
#include <Text.h>
#include <TweenEngine.h>

#include "Breakout.h"
#include "GlobalSettings.h"
#include "Resources.h"
#include "ScoreScreen.h"

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


    Input::AddInputAction(bout::InputActionName::CheatOpenMainMenu, { { SDL_SCANCODE_1 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenGame, { { SDL_SCANCODE_2 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenWinScreen, { { SDL_SCANCODE_3 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenLoseScreen, { { SDL_SCANCODE_4 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenScoreScreen, { { SDL_SCANCODE_5 } });


    Input::AddInputAction(bout::InputActionName::CheatSpawnBall, { { SDL_SCANCODE_B } });
    Input::AddInputAction(bout::InputActionName::CheatClearField, { { SDL_SCANCODE_C } });

    Input::AddInputAction(bout::InputActionName::PauseGame,
                          {
                              {SDL_SCANCODE_P, SDL_SCANCODE_ESCAPE}
    });
    Input::AddInputAction(bout::InputActionName::FireBall, { { SDL_SCANCODE_SPACE }, true });


    SceneGraph::BindScene(bout::SceneName::Game, []() { bin::SceneGraph::AddNode<bout::Breakout>(); });

    SceneGraph::BindScene(bout::SceneName::MainMenuScreen, []() { bin::SceneGraph::AddNode<bout::MainMenu>(); });

    SceneGraph::BindScene(
        bout::SceneName::GameWonScreen,
        []()
        {
            bin::SceneGraph::AddNode<bin::Camera>();

            auto& winnerText = bin::SceneGraph::AddNode<bin::Text>("YOU WIN!",
                                                                   bin::Resources::GetFont(bout::FontName::NES_Font),
                                                                   glm::vec2{ 0.5f, 0.5f },
                                                                   3.0f,
                                                                   SDL_Color{ 60, 240, 100, 255 });

            // Show text
            bin::TweenEngine::Start({ .from = -15.0f,
                                      .to = 0.0f,
                                      .duration = 1.0f,
                                      .easeType = EaseType::ElasticOut,
                                      .onUpdate =
                                          [&winnerText](float value) {
                                              winnerText.SetLocalPosition({ 0, value });
                                          } },
                                    winnerText);

            // Hide text
            bin::TweenEngine::Start({ .delay = 2.0f,
                                      .from = winnerText.GetLocalPosition().y,
                                      .to = 15.0f,
                                      .duration = 1.0f,
                                      .easeType = EaseType::SineIn,
                                      .onUpdate =
                                          [&winnerText](float value) {
                                              winnerText.SetLocalPosition({ 0, value });
                                          },
                                      .onEnd = []() { bin::SceneGraph::LoadScene(bout::SceneName::ScoreScreen); } },
                                    winnerText);
        });

    SceneGraph::BindScene(
        bout::SceneName::GameLostScreen,
        []()
        {
            bin::SceneGraph::AddNode<bin::Camera>();

            auto& winnerText = bin::SceneGraph::AddNode<bin::Text>("YOU LOSE",
                                                                   bin::Resources::GetFont(bout::FontName::NES_Font),
                                                                   glm::vec2{ 0.5f, 0.5f },
                                                                   3.0f,
                                                                   SDL_Color{ 240, 60, 100, 255 });

            // Show text
            bin::TweenEngine::Start({ .from = -15.0f,
                                      .to = 0.0f,
                                      .duration = 1.0f,
                                      .easeType = EaseType::SineOut,
                                      .onUpdate =
                                          [&winnerText](float value) {
                                              winnerText.SetLocalPosition({ 0, value });
                                          } },
                                    winnerText);

            // Hide text
            bin::TweenEngine::Start({ .delay = 2.0f,
                                      .from = winnerText.GetLocalPosition().y,
                                      .to = 15.0f,
                                      .duration = 1.0f,
                                      .easeType = EaseType::SineIn,
                                      .onUpdate =
                                          [&winnerText](float value) {
                                              winnerText.SetLocalPosition({ 0, value });
                                          },
                                      .onEnd = []() { bin::SceneGraph::LoadScene(bout::SceneName::ScoreScreen); } },
                                    winnerText);
        });


    SceneGraph::BindScene(bout::SceneName::ScoreScreen, []() { bin::SceneGraph::AddNode<bin::ScoreScreen>(); });


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


    Input::Bind(bout::InputActionName::CheatOpenMainMenu,
                [](const InputContext& context)
                {
                    if(context.state != bin::ButtonState::Down)
                        return;

                    bin::SceneGraph::LoadScene(bout::SceneName::MainMenuScreen);
                });

    Input::Bind(bout::InputActionName::CheatOpenGame,
                [](const InputContext& context)
                {
                    if(context.state != bin::ButtonState::Down)
                        return;

                    bin::SceneGraph::LoadScene(bout::SceneName::Game);
                });

    Input::Bind(bout::InputActionName::CheatOpenWinScreen,
                [](const InputContext& context)
                {
                    if(context.state != bin::ButtonState::Down)
                        return;

                    bin::SceneGraph::LoadScene(bout::SceneName::GameWonScreen);
                });

    Input::Bind(bout::InputActionName::CheatOpenLoseScreen,
                [](const InputContext& context)
                {
                    if(context.state != bin::ButtonState::Down)
                        return;

                    bin::SceneGraph::LoadScene(bout::SceneName::GameLostScreen);
                });

    Input::Bind(bout::InputActionName::CheatOpenScoreScreen,
                [](const InputContext& context)
                {
                    if(context.state != bin::ButtonState::Down)
                        return;

                    bin::SceneGraph::LoadScene(bout::SceneName::ScoreScreen);
                });

    SceneGraph::LoadScene(bout::SceneName::MainMenuScreen);
}
