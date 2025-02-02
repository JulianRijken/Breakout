#include <Audio.h>
#include <Core.h>
#include <Input.h>
#include <SceneGraph.h>
#include <Text.h>

#include "GlobalSettings.h"
#include "Resources.h"
#include "Scenes.h"

bin::InitSettings bin::Core::Configure() const
{
    // clang-format off
    return {
        .windowSize = { 1280, 720 },
        .windowTitle = "Breakout - By Julian Rijken"
    };
    // clang-format on
}

void bin::Core::GameEntry()
{
    Audio::SetGlobalVolume(0.4f);

    Resources::LoadFont(bout::FontName::NES_Font, "Fonts/NES_Font.ttf", 8);
    Resources::LoadSound(bout::SoundName::WallHit, "Sounds/Tetris_WallHit.ogg");
    Resources::LoadSound(bout::SoundName::PaddleHit, "Sounds/Custom_PaddleHit.ogg");
    Resources::LoadSound(bout::SoundName::BrickBreak, "Sounds/Custom_BrickBreak.ogg");
    Resources::LoadSound(bout::SoundName::ButtonPress, "Sounds/Kenney_ButtonPress.ogg");
    Resources::LoadSound(bout::SoundName::ButtonRelease, "Sounds/Kenney_ButtonRelease.ogg");
    Resources::LoadSound(bout::SoundName::ButtonHover, "Sounds/Tetris_ButtonHover.ogg");
    Resources::LoadSound(bout::SoundName::GameStart, "Sounds/Tetris_GameStart.ogg");
    Resources::LoadSound(bout::SoundName::GameLost, "Sounds/Tetris_GameLost.ogg");
    Resources::LoadSound(bout::SoundName::GameWon, "Sounds/Tetris_GameWon.ogg");
    Resources::LoadSound(bout::SoundName::GameStartup, "Sounds/BubbleBobble_Startup.ogg");
    Resources::LoadSound(bout::SoundName::PauseGame, "Sounds/Kenney_ButtonPress.ogg");
    Resources::LoadSound(bout::SoundName::UnPauseGame, "Sounds/Kenney_ButtonRelease.ogg");
    Resources::LoadSound(bout::SoundName::BallLost, "Sounds/BubbleBobble_BallLost.ogg");

    Input::AddInputAction(bout::InputActionName::CheatOpenMainMenu, { .keyboardButtons{ SDL_SCANCODE_1 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenGame, { .keyboardButtons{ SDL_SCANCODE_2 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenWinScreen, { .keyboardButtons{ SDL_SCANCODE_3 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenLoseScreen, { .keyboardButtons{ SDL_SCANCODE_4 } });
    Input::AddInputAction(bout::InputActionName::CheatOpenScoreScreen, { .keyboardButtons{ SDL_SCANCODE_5 } });
    Input::AddInputAction(bout::InputActionName::CheatSpawnBall, { .keyboardButtons{ SDL_SCANCODE_B } });
    Input::AddInputAction(bout::InputActionName::CheatClearField, { .keyboardButtons{ SDL_SCANCODE_C } });
    Input::AddInputAction(bout::InputActionName::PauseGame,
                          {
                              .keyboardButtons{ SDL_SCANCODE_P, SDL_SCANCODE_ESCAPE }
    });
    Input::AddInputAction(bout::InputActionName::FireBall,
                          { .keyboardButtons{ SDL_SCANCODE_SPACE }, .leftMouseButton = true });


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
