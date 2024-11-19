#include "HUD.h"

#include <fmt/core.h>
#include <Font.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <Texture.h>

#include "GameStats.h"
#include "GlobalSettings.h"

bout::HUD::HUD(GameStats& gameStats)
{
    m_ScoreText = &bin::SceneGraph::AddNode<bin::Text>(
        "SCORE 0", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 1.8f);
    m_ScoreText->SetParent(this);
    m_ScoreText->SetLocalPosition({ 0, 9 });

    m_BallsLeftText = &bin::SceneGraph::AddNode<bin::Text>("BALLS LEFT 0",
                                                           bin::Resources::GetFont(FontName::NES_Font),
                                                           glm::vec2{ 0.5f, 0.5f },
                                                           0.8f,
                                                           SDL_Color{ 200, 200, 200, 255 });
    m_BallsLeftText->SetParent(this);
    m_BallsLeftText->SetLocalPosition({ 0, 7.0f });

    gameStats.m_OnScoreChanged.AddListener(this, &bout::HUD::OnScoreChanged);
}

void bout::HUD::OnScoreChanged(int score)
{
    const std::string text = fmt::format("SCORE {}", score);
    m_ScoreText->SetText(text);
}
