#include <Audio.h>
#include <Core.h>
#include <Input.h>
#include <SceneGraph.h>
#include <Text.h>

#include "GlobalSettings.h"
#include "Resources.h"
#include "Scenes.h"

void bin::Core::PreInit(bin::InitSettings& settings)
{
    settings.windowWidth = 1280;
    settings.windowHeight = 720;
    settings.windowTitle = "Breakout - By Julian Rijken";
}

void bin::Core::GameEntry()
{
    Audio::SetGlobalVolume(0.4f);

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
    Resources::LoadSound(bout::SoundName::GameStartup, "Sounds/BubbleBobble_Startup.ogg");
    Resources::LoadSound(bout::SoundName::PauseGame, "Sounds/Kenney_ButtonPress.ogg");
    Resources::LoadSound(bout::SoundName::UnPauseGame, "Sounds/Kenney_ButtonRelease.ogg");
    Resources::LoadSound(bout::SoundName::BallLost, "Sounds/BubbleBobble_BallLost.ogg");

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


    SceneGraph::BindScene(bout::SceneName::Game, bout::scenes::GameScene);
    SceneGraph::BindScene(bout::SceneName::MainMenu, bout::scenes::MainMenuScene);
    SceneGraph::BindScene(bout::SceneName::GameWon, bout::scenes::GameWonScene);
    SceneGraph::BindScene(bout::SceneName::GameLost, bout::scenes::GameLostScene);
    SceneGraph::BindScene(bout::SceneName::Score, bout::scenes::ScoreScene);


    Input::Bind(bout::InputActionName::CheatOpenMainMenu,
                [](const InputContext& context)
                {
                    if(context.state == bin::ButtonState::Down)
                        bin::SceneGraph::LoadScene(bout::SceneName::MainMenu);
                });

    Input::Bind(bout::InputActionName::CheatOpenGame,
                [](const InputContext& context)
                {
                    if(context.state == bin::ButtonState::Down)
                        bin::SceneGraph::LoadScene(bout::SceneName::Game);
                });

    Input::Bind(bout::InputActionName::CheatOpenWinScreen,
                [](const InputContext& context)
                {
                    if(context.state == bin::ButtonState::Down)
                        bin::SceneGraph::LoadScene(bout::SceneName::GameWon);
                });

    Input::Bind(bout::InputActionName::CheatOpenLoseScreen,
                [](const InputContext& context)
                {
                    if(context.state == bin::ButtonState::Down)
                        bin::SceneGraph::LoadScene(bout::SceneName::GameLost);
                });

    Input::Bind(bout::InputActionName::CheatOpenScoreScreen,
                [](const InputContext& context)
                {
                    if(context.state == bin::ButtonState::Down)
                        bin::SceneGraph::LoadScene(bout::SceneName::Score);
                });

    // Play little sound for the user to know it works
    Audio::Play(bout::SoundName::GameStartup);

    // Load main scene by default
    SceneGraph::LoadScene(bout::SceneName::MainMenu);
}
