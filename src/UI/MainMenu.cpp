#include "MainMenu.h"

#include <Audio.h>
#include <Button.h>
#include <Font.h>
#include <GameTime.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <TweenEngine.h>

#include "GlobalSettings.h"
#include "Prefabs.h"

bout::MainMenu::MainMenu()
{
    // Reset time scale
    bin::GameTime::SetTimeScale(1.0f);

    auto& camera = bin::SceneGraph::AddNode<bin::Camera>();
    camera.SetOrthoSize(10);

    auto& title = bin::SceneGraph::AddNode<bin::Text>(
        "", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 2.0f);
    title.SetParent(this);
    title.SetLocalPosition({ 0, 6 });

    auto& subTitle = bin::SceneGraph::AddNode<bin::Text>(
        "", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 0.8f, SDL_Color(200, 200, 200, 255));
    subTitle.SetParent(this);
    subTitle.SetLocalPosition({ 0, 4 });

    auto& startButton = prefabs::TextButton({ 10, 2 }, "START", *this);
    startButton.SetParent(this);
    startButton.SetLocalPosition({ 0, -15 });
    startButton.m_OnReleased.AddListener(this, &MainMenu::OnStartButtonPress);
    startButton.SetOnHoverSound(SoundName::ButtonHover);
    startButton.SetOnPressSound(SoundName::ButtonPress);
    startButton.SetOnReleasedSound(SoundName::ButtonRelease);


    auto& quitButton = prefabs::TextButton({ 10, 2 }, "QUIT", *this);
    quitButton.SetParent(this);
    quitButton.SetLocalPosition({ 0, -15 });
    quitButton.m_OnReleased.AddListener(this, &MainMenu::OnQuitButtonPress);
    quitButton.SetOnHoverSound(SoundName::ButtonHover);
    quitButton.SetOnPressSound(SoundName::ButtonPress);
    quitButton.SetOnReleasedSound(SoundName::ButtonRelease);


    // Animate Title
    bin::TweenEngine::Start(
        {
            .duration = 0.5f,
            .onUpdate =
                [&title](float value)
            {
                const std::string toText = bin::math::TextCutoff("BREAKOUT", value);
                title.SetText(toText);
            },
        },
        title);

    // Animate Subtitle
    bin::TweenEngine::Start(
        {
            .delay = 0.8f,
            .duration = 0.8f,
            .onUpdate =
                [&subTitle](float value)
            {
                const std::string toText = bin::math::TextCutoff("BY JULIAN RIJKEN", value);
                subTitle.SetText(toText);
            },
        },
        subTitle);

    // Animate Start Button
    bin::TweenEngine::Start(
        {
            .delay = 1.5f,
            .from = startButton.GetLocalPosition().y,
            .to = 1.0f,
            .duration = 0.8f,
            .easeType = bin::EaseType::SineOut,
            .onUpdate =
                [&startButton](float value) {
                    startButton.SetLocalPosition({ 0.0f, value });
                },
        },
        startButton);

    // Animate Quit Button
    bin::TweenEngine::Start(
        {
            .delay = 0.3f + 1.5f,
            .from = quitButton.GetLocalPosition().y,
            .to = -3.0f,
            .duration = 0.8f,
            .easeType = bin::EaseType::SineOut,
            .onUpdate =
                [&quitButton](float value) {
                    quitButton.SetLocalPosition({ 0.0f, value });
                },
        },
        quitButton);
}

void bout::MainMenu::OnStartButtonPress()
{
    if(m_StartingGame)
        return;

    m_StartingGame = true;

    // Move main menu to the top and load game scene
    bin::TweenEngine::Start({ .from = 0.0f,
                              .to = 20.0f,
                              .duration = 0.8f,
                              .easeType = bin::EaseType::SineIn,
                              .onUpdate =
                                  [this](float value) {
                                      SetLocalPosition({ 0.0f, value });
                                  },
                              .onEnd = []() { bin::SceneGraph::LoadScene(SceneName::Game); } },
                            *this);
}

void bout::MainMenu::OnQuitButtonPress()
{
    if(m_StartingGame)
        return;

    SDL_Quit();
}
