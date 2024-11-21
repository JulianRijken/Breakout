#include "PauseMenu.h"

#include <Button.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Sprite.h>
#include <Text.h>
#include <TweenEngine.h>

#include "GlobalSettings.h"
#include "Prefabs.h"

bout::PauseMenu::PauseMenu()
{
    auto& backgroundEdge = bin::SceneGraph::AddNode<bin::Sprite>(SDL_Color{ 100, 120, 200, 255 });
    backgroundEdge.SetParent(this);
    backgroundEdge.SetLocalScale({ 16, 30 });

    auto& background = bin::SceneGraph::AddNode<bin::Sprite>(SDL_Color{ 25, 25, 25, 255 });
    background.SetParent(this);
    background.SetLocalScale({ 15, 30 });

    auto& title = bin::SceneGraph::AddNode<bin::Text>(
        "PAUSED", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 2.0f);
    title.SetParent(this);
    title.SetLocalPosition({ 0, 4 });

    auto& returnButton = prefabs::TextButton({ 10, 2 }, "QUIT", *this);
    returnButton.SetParent(this);
    returnButton.SetLocalPosition({ 0, 0 });
    returnButton.m_OnReleased.AddListener([] { bin::SceneGraph::LoadScene(SceneName::MainMenu); });
    returnButton.SetOnHoverSound(SoundName::ButtonHover);
    returnButton.SetOnPressSound(SoundName::ButtonPress);
    returnButton.SetOnReleasedSound(SoundName::ButtonRelease);

    bin::TweenEngine::Start(
        {
            .duration = ANIMATION_DURATION,
            .ignoreTimeScale = true,
            .easeType = bin::EaseType::SineOut,
            .onUpdate =
                [this](float value)
            {
                glm::vec2 scale = GetLocalScale();
                scale.x = value;
                SetLocalScale(scale);
            },
        },
        *this);
}

void bout::PauseMenu::HideAndDestroy()
{
    bin::TweenEngine::Start({ .from = 1.0f,
                              .to = 0.0f,
                              .duration = ANIMATION_DURATION,
                              .ignoreTimeScale = true,
                              .easeType = bin::EaseType::SineIn,
                              .onUpdate =
                                  [this](float value)
                              {
                                  glm::vec2 scale = GetLocalScale();
                                  scale.x = value;
                                  SetLocalScale(scale);
                              },
                              .onEnd = [this]() { MarkForDestroy(); } },
                            *this);
}
