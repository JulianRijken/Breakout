#include "HUD.h"

#include <fmt/core.h>
#include <MessageQueue.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Shaker.h>
#include <Text.h>
#include <TweenEngine.h>

#include "GameState.h"
#include "GlobalSettings.h"
#include "MathExtensions.h"

bout::HUD::HUD()
{
    m_ScoreText = &bin::SceneGraph::AddNode<bin::Text>(
        "SCORE 0", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 1.8f);
    m_ScoreText->SetParent(this);
    m_ScoreText->SetLocalPosition({ 0, 9 });


    m_BallsLeftShaker = &bin::SceneGraph::AddNode<bin::Shaker>(0.0f, 0.04f, 0.05f, false);
    m_BallsLeftShaker->SetParent(this);

    m_BallsLeftText = &bin::SceneGraph::AddNode<bin::Text>(
        "BALLS LEFT _", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 0.8f, FULL_BALLS_COLOR);
    m_BallsLeftText->SetParent(m_BallsLeftShaker);
    m_BallsLeftText->SetLocalPosition({ 0, 7.0f });


    m_LaunchBallText = &bin::SceneGraph::AddNode<bin::Text>("LAUNCH BALL",
                                                            bin::Resources::GetFont(FontName::NES_Font),
                                                            glm::vec2{ 0.5f, 0.5f },
                                                            0.0f,
                                                            SDL_Color{ 200, 200, 200, 255 });
    m_LaunchBallText->SetParent(this);
    m_LaunchBallText->SetLocalPosition({ 0, -5 });


    GameState::GetInstance().m_OnScoreChanged.AddListener(this, &bout::HUD::OnScoreChanged);
    GameState::GetInstance().m_OnBallsLeftChanged.AddListener(this, &bout::HUD::OnBallsLeftChanged);

    bin::MessageQueue::AddListener(MessageType::BallLaunched, this, &HUD::OnBallLaunchedMessage);
    bin::MessageQueue::AddListener(MessageType::BallSpawned, this, &HUD::OnBallSpawnedMessage);
}

bout::HUD::~HUD() { bin::MessageQueue::RemoveListenerInstance(this); }

void bout::HUD::OnScoreChanged(int score)
{
    const std::string text = fmt::format("SCORE {}", score);
    m_ScoreText->SetText(text);

    bin::TweenEngine::Start({ .from = 1.2f,
                              .to = 1.8f,
                              .duration = 1.0f,
                              .easeType = bin::EaseType::BounceOut,
                              .onUpdate = [this](float value) { m_ScoreText->SetSize(value); } },
                            *this);
}

void bout::HUD::OnBallsLeftChanged(int ballsLeft)
{
    const std::string text = ballsLeft > 0 ? fmt::format("BALLS LEFT {}", ballsLeft) : "NO BALLS LEFT";
    m_BallsLeftText->SetText(text);

    // TODO: Get rid of magic number 4.0f which is the balls count
    float alpha = static_cast<float>(ballsLeft) / 4.0f;

    m_BallsLeftText->SetColor(bin::math::Lerp(NO_BALLS_COLOR, FULL_BALLS_COLOR, alpha));
    m_BallsLeftShaker->SetStrength(bin::math::Lerp(NO_BALLS_SHAKE_STRENGTH, FULL_BALLS_SHAKE_STRENGTH, alpha));
}

void bout::HUD::OnBallLaunchedMessage(const bin::Message& /*unused*/)
{
    bin::TweenEngine::Start({ .from = LAUNCH_BALL_TEXT_SIZE,
                              .to = 0.0f,
                              .duration = LAUNCH_BALL_TEXT_SHOW_DURATION,
                              .easeType = bin::EaseType::SineOut,
                              .onUpdate = [this](float value) { m_LaunchBallText->SetSize(value); } },
                            *this);
}

void bout::HUD::OnBallSpawnedMessage(const bin::Message& /*unused*/)
{
    bin::TweenEngine::Start({ .from = 0.0f,
                              .to = LAUNCH_BALL_TEXT_SIZE,
                              .duration = LAUNCH_BALL_TEXT_SHOW_DURATION,
                              .easeType = bin::EaseType::SineOut,
                              .onUpdate = [this](float value) { m_LaunchBallText->SetSize(value); } },
                            *this);
}
