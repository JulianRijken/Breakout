#include "HUD.h"

#include <fmt/core.h>
#include <Font.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <Texture.h>

#include "GameStats.h"

bout::HUD::HUD(GameStats& gameStats)
{
    m_ScoreText = &bin::SceneGraph::AddNode<bin::Text>("SCORE", bin::Resources::GetFont(0), glm::vec2{ 0.5f, 0.5f });
    m_ScoreText->SetParent(this);
    m_ScoreText->SetLocalPosition({ 0, 0 });

    gameStats.m_OnScoreChanged.AddListener(this, &bout::HUD::OnScoreChanged);
}

void bout::HUD::OnScoreChanged(int score)
{
    std::string text = fmt::format("SCORE: {}", score);
    m_ScoreText->SetText(text);
}
