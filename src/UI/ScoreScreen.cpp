#include "ScoreScreen.h"

#include <Button.h>
#include <Camera.h>
#include <fmt/format.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>

#include "GameState.h"
#include "GlobalSettings.h"
#include "Prefabs.h"
#include "TweenEngine.h"

bout::ScoreScreen::ScoreScreen()
{
    auto& camera = bin::SceneGraph::AddNode<bin::Camera>();
    camera.SetOrthoSize(11);

    auto& title = bin::SceneGraph::AddNode<bin::Text>(
        "GAME STATS", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 2.0f);
    title.SetParent(this);
    title.SetLocalPosition({ 0, 6 });

    if(not GameState::GetInstance().HasCheated())
        ShowStats();
    else
    {
        auto& cheatText = bin::SceneGraph::AddNode<bin::Text>(fmt::format("YOU CHEATED!"),
                                                              bin::Resources::GetFont(FontName::NES_Font),
                                                              glm::vec2{ 0.5f, 0.5f },
                                                              1.5f,
                                                              SDL_Color(235, 59, 59, 255));
        cheatText.SetParent(this);
        cheatText.SetLocalPosition({ 0, 0 });
    }

    auto& returnButton = prefabs::TextButton({ 10, 2 }, "RETURN", *this);
    returnButton.SetParent(this);
    returnButton.SetLocalPosition({ 0, -7 });
    returnButton.m_OnReleased.AddListener(this, &ScoreScreen::ExitScren);
    returnButton.SetOnHoverSound(SoundName::ButtonHover);
    returnButton.SetOnPressSound(SoundName::ButtonPress);
    returnButton.SetOnReleasedSound(SoundName::ButtonRelease);

    // Animate screen in
    bin::TweenEngine::Start({ .duration = 1.5f,
                              .easeType = bin::EaseType::ElasticOut,
                              .onUpdate =
                                  [this](float value) {
                                      SetLocalScale({ value, value });
                                  } },
                            *this);
}

void bout::ScoreScreen::ShowStats()
{
    constexpr float textSpacing = 1.5f;
    constexpr float textPosition = 3.0f;

    auto& difficultyText = bin::SceneGraph::AddNode<bin::Text>(
        fmt::format("DIFFUCULTY: {}", GameState::GetInstance().GetDifficultyPreset().name),
        bin::Resources::GetFont(FontName::NES_Font),
        glm::vec2{ 0.5f, 0.5f },
        0.8f,
        SDL_Color(200, 200, 200, 255));
    difficultyText.SetParent(this);
    difficultyText.SetLocalPosition({ 0, textPosition - textSpacing * 0 });


    const int timePlayedInSeconds = GameState::GetInstance().GetScecondsSinceGameReset();
    const int minutes = timePlayedInSeconds / 60;
    const int seconds = timePlayedInSeconds % 60;
    auto& timePlayedText =
        bin::SceneGraph::AddNode<bin::Text>(fmt::format("TIME PLAYED: {:02}:{:02}", minutes, seconds),
                                            bin::Resources::GetFont(FontName::NES_Font),
                                            glm::vec2{ 0.5f, 0.5f },
                                            0.8f,
                                            SDL_Color(200, 200, 200, 255));
    timePlayedText.SetParent(this);
    timePlayedText.SetLocalPosition({ 0, textPosition - textSpacing * 1 });

    auto& ballsLost =
        bin::SceneGraph::AddNode<bin::Text>(fmt::format("BALLS LOST: {}", GameState::GetInstance().GetBallsLost()),
                                            bin::Resources::GetFont(FontName::NES_Font),
                                            glm::vec2{ 0.5f, 0.5f },
                                            0.8f,
                                            SDL_Color(200, 200, 200, 255));
    ballsLost.SetParent(this);
    ballsLost.SetLocalPosition({ 0, textPosition - textSpacing * 2 });

    auto& bricksBrokenText = bin::SceneGraph::AddNode<bin::Text>(
        fmt::format("BRICKS BROKEN: {}", GameState::GetInstance().GetBricksBroken()),
        bin::Resources::GetFont(FontName::NES_Font),
        glm::vec2{ 0.5f, 0.5f },
        0.8f,
        SDL_Color(200, 200, 200, 255));
    bricksBrokenText.SetParent(this);
    bricksBrokenText.SetLocalPosition({ 0, textPosition - textSpacing * 3 });


    auto& paddleBouncesText = bin::SceneGraph::AddNode<bin::Text>(
        fmt::format("PADDLE BOUNCES: {}", GameState::GetInstance().GetPaddleBounces()),
        bin::Resources::GetFont(FontName::NES_Font),
        glm::vec2{ 0.5f, 0.5f },
        0.8f,
        SDL_Color(200, 200, 200, 255));
    paddleBouncesText.SetParent(this);
    paddleBouncesText.SetLocalPosition({ 0, textPosition - textSpacing * 4 });
}

void bout::ScoreScreen::ExitScren()
{
    // Animate screen out
    bin::TweenEngine::Start({ .from = 1.0f,
                              .to = 0.0f,
                              .duration = 1.5f,
                              .easeType = bin::EaseType::ElasticIn,
                              .onUpdate =
                                  [this](float value) {
                                      SetLocalScale({ value, value });
                                  },
                              .onEnd = [] { bin::SceneGraph::LoadScene(SceneName::MainMenu); } },
                            *this);
}
