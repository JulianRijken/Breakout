#include "Scenes.h"

#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <TweenEngine.h>

#include "Breakout.h"
#include "GlobalSettings.h"
#include "MainMenu.h"
#include "ScoreScreen.h"

void bout::scenes::MainMenuScene() { bin::SceneGraph::AddNode<bout::MainMenu>(); }

void bout::scenes::GameScene() { bin::SceneGraph::AddNode<bout::Breakout>(); }

void bout::scenes::GameWonScene()
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
                              .easeType = bin::EaseType::ElasticOut,
                              .onUpdate = [&winnerText](float value) { winnerText.SetLocalPosition({ 0, value }); } },
                            winnerText);

    // Hide text
    bin::TweenEngine::Start({ .delay = 2.0f,
                              .from = winnerText.GetLocalPosition().y,
                              .to = 15.0f,
                              .duration = 1.0f,
                              .easeType = bin::EaseType::SineIn,
                              .onUpdate = [&winnerText](float value) { winnerText.SetLocalPosition({ 0, value }); },
                              .onEnd = []() { bin::SceneGraph::LoadScene(bout::SceneName::Score); } },
                            winnerText);
}

void bout::scenes::GameLostScene()
{
    bin::SceneGraph::AddNode<bin::Camera>();

    auto& loserText = bin::SceneGraph::AddNode<bin::Text>("YOU LOSE",
                                                          bin::Resources::GetFont(bout::FontName::NES_Font),
                                                          glm::vec2{ 0.5f, 0.5f },
                                                          3.0f,
                                                          SDL_Color{ 240, 60, 100, 255 });

    // Show text
    bin::TweenEngine::Start({ .from = -15.0f,
                              .to = 0.0f,
                              .duration = 1.0f,
                              .easeType = bin::EaseType::SineOut,
                              .onUpdate = [&loserText](float value) { loserText.SetLocalPosition({ 0, value }); } },
                            loserText);

    // Hide text
    bin::TweenEngine::Start({ .delay = 2.0f,
                              .from = loserText.GetLocalPosition().y,
                              .to = 15.0f,
                              .duration = 1.0f,
                              .easeType = bin::EaseType::SineIn,
                              .onUpdate = [&loserText](float value) { loserText.SetLocalPosition({ 0, value }); },
                              .onEnd = []() { bin::SceneGraph::LoadScene(bout::SceneName::Score); } },
                            loserText);
}

void bout::scenes::ScoreScene() { bin::SceneGraph::AddNode<ScoreScreen>(); }
