#include "MainMenu.h"

#include <Audio.h>
#include <Button.h>
#include <Core.h>
#include <Font.h>
#include <GameTime.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <TweenEngine.h>

#include "GameState.h"
#include "GlobalSettings.h"
#include "Prefabs.h"

bout::MainMenu::MainMenu()
{
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


    auto infoText = [this](const std::string& content, float offset, float size, SDL_Color color) -> bin::Text&
    {
        constexpr float infoTextSpacing = 0.9f;
        constexpr glm::vec2 infoTextPosition = { -16.0f, 1.0f };

        auto& text = bin::SceneGraph::AddNode<bin::Text>(
            content, bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.0f, 0.5f }, size);
        text.SetParent(this);
        text.SetLocalPosition({ 1000, 1000 });  // TODO: add setting active to nodes lol

        const glm::vec2 targetPosition = { infoTextPosition.x, infoTextPosition.y - infoTextSpacing * offset };

        // Animate Slide In
        bin::TweenEngine::Start(
            {
                .delay = offset * 0.5f + 2.0f,
                .duration = 1.0f,
                .easeType = bin::EaseType::SineOut,
                .onUpdate =
                    [&text, targetPosition, color](float value)
                {
                    constexpr float slideInDistance = 30.0f;
                    const std::string toText = bin::math::TextCutoff("BREAKOUT", value);
                    text.SetLocalPosition(
                        bin::math::Lerp(targetPosition - glm::vec2{ slideInDistance, 0.0f }, targetPosition, value));
                    text.SetColor(bin::math::Lerp({ color.r, color.g, color.b, 0 }, color, value));
                },
            },
            text);

        return text;
    };

    constexpr float infoTextHeaderSize = 0.65f;
    constexpr float infoTextSize = 0.4f;
    infoText("HOW TO PLAY", 1, infoTextHeaderSize, SDL_Color(200, 200, 200, 255));
    infoText("- USE MOUSE TO FIRE", 2, infoTextSize, SDL_Color(150, 150, 150, 255));
    infoText("- USE R TO PAUSE", 3, infoTextSize, SDL_Color(150, 150, 150, 255));
    infoText("- USE C TO CHEAT CLEAR", 4, infoTextSize, SDL_Color(150, 150, 150, 255));
    infoText("- USE B TO CHEAT BALL", 5, infoTextSize, SDL_Color(150, 150, 150, 255));


    auto& startButton = prefabs::TextButton({ 10, 2 }, "START", *this);
    startButton.SetParent(this);
    startButton.SetLocalPosition({ 0, -15 });
    startButton.m_OnReleased.AddListener(this, &MainMenu::OnStartButtonPress);
    startButton.SetOnHoverSound(SoundName::ButtonHover);
    startButton.SetOnPressSound(SoundName::ButtonPress);
    startButton.SetOnReleasedSound(SoundName::ButtonRelease);

    auto& difficultyButton = prefabs::TextButton({ 10, 2 }, "", *this);
    difficultyButton.SetParent(this);
    difficultyButton.SetLocalPosition({ 0, -15 });
    difficultyButton.m_OnReleased.AddListener(this, &MainMenu::OnDifficultyButtonPress);
    difficultyButton.SetOnHoverSound(SoundName::ButtonHover);
    difficultyButton.SetOnPressSound(SoundName::ButtonPress);
    difficultyButton.SetOnReleasedSound(SoundName::ButtonRelease);

    m_DifficultyButtonText = difficultyButton.GetFirstChildNodeOfType<bin::Text>();

    auto& quitButton = prefabs::TextButton({ 10, 2 }, "QUIT", *this);
    quitButton.SetParent(this);
    quitButton.SetLocalPosition({ 0, -15 });
    quitButton.m_OnReleased.AddListener(this, &MainMenu::OnQuitButtonPress);
    quitButton.SetOnHoverSound(SoundName::ButtonHover);
    quitButton.SetOnPressSound(SoundName::ButtonPress);
    quitButton.SetOnReleasedSound(SoundName::ButtonRelease);

    // Reset time scale
    bin::GameTime::SetTimeScale(1.0f);
    SetDifficulty(GameState::GetInstance().m_Difficulty);


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

    constexpr float showButtonDelay = 1.5f;
    constexpr float buttonBetweenDelay = 0.3f;
    constexpr float animateDuration = 0.8f;
    constexpr float buttonOffset = 1.0f;
    constexpr float buttonBottemPadding = 3.0f;

    // Animate Start Button
    bin::TweenEngine::Start(
        {
            .delay = showButtonDelay,
            .from = startButton.GetLocalPosition().y,
            .to = buttonOffset,
            .duration = animateDuration,
            .easeType = bin::EaseType::SineOut,
            .onUpdate =
                [&startButton](float value) {
                    startButton.SetLocalPosition({ 0.0f, value });
                },
        },
        startButton);


    // Animate Difficulty Button
    bin::TweenEngine::Start(
        {
            .delay = buttonBetweenDelay * 1 + showButtonDelay,
            .from = quitButton.GetLocalPosition().y,
            .to = buttonOffset - buttonBottemPadding * 1,
            .duration = animateDuration,
            .easeType = bin::EaseType::SineOut,
            .onUpdate =
                [&difficultyButton](float value) {
                    difficultyButton.SetLocalPosition({ 0.0f, value });
                },
        },
        difficultyButton);

    // Animate Quit Button
    bin::TweenEngine::Start(
        {
            .delay = buttonBetweenDelay * 2 + showButtonDelay,
            .from = quitButton.GetLocalPosition().y,
            .to = buttonOffset - buttonBottemPadding * 2,
            .duration = animateDuration,
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

void bout::MainMenu::OnDifficultyButtonPress()
{
    if(m_StartingGame)
        return;

    // Todo could be done automatically with a enum and size
    // but kept for simplicty
    switch(GameState::GetInstance().m_Difficulty)
    {
        case bout::Difficulty::Noob:
            SetDifficulty(Difficulty::Easy);
            break;
        case bout::Difficulty::Easy:
            SetDifficulty(Difficulty::Hard);
            break;
        case bout::Difficulty::Hard:
            SetDifficulty(Difficulty::Nerd);
            break;
        case bout::Difficulty::Nerd:
            SetDifficulty(Difficulty::Noob);
            break;
    }
}

void bout::MainMenu::OnQuitButtonPress()
{
    if(m_StartingGame)
        return;

    bin::Core::QuitGame();
}

void bout::MainMenu::SetDifficulty(Difficulty difficulty)
{
    GameState::GetInstance().m_Difficulty = difficulty;

    switch(difficulty)
    {
        case bout::Difficulty::Noob:
            m_DifficultyButtonText->SetText("NOOB");
            break;
        case bout::Difficulty::Easy:
            m_DifficultyButtonText->SetText("EASY");
            break;
        case bout::Difficulty::Hard:
            m_DifficultyButtonText->SetText("HARD");
            break;
        case bout::Difficulty::Nerd:
            m_DifficultyButtonText->SetText("NERD");
            break;
    }
}
