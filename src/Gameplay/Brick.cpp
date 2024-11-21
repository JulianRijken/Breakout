#include "Brick.h"

#include <Audio.h>
#include <BoxCollider.h>
#include <MessageQueue.h>
#include <Renderer.h>
#include <SceneGraph.h>
#include <Sprite.h>
#include <TweenEngine.h>

#include "GlobalSettings.h"
#include "Resources.h"

bout::Brick::Brick(int pointsWorth, const SDL_Color& brickColor) :
    m_PointsWorth(pointsWorth)
{
    m_SpritePtr = &bin::SceneGraph::AddNode<bin::Sprite>(brickColor);
    m_SpritePtr->SetParent(this);

    m_BoxColliderPtr =
        &bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 1.0f, 1.0f }, bout::collisionLayer::BRICK);
    m_BoxColliderPtr->SetParent(this);
    m_BoxColliderPtr->m_OnHit.AddListener(this, &Brick::OnHit);
}

void bout::Brick::Break()
{
    if(m_BoxColliderPtr == nullptr)
        return;

    bin::MessageQueue::Broadcast(MessageType::BrickBreak, { m_PointsWorth });
    bin::Audio::Play(bin::Resources::GetSound(SoundName::BrickBreak));

    const float randomRotationDistance =
        bin::math::RandomRange(300.0f, 600.0f) * (bin::math::RandomValue() > 0.5f ? -1.0f : 1.0f);

    const SDL_Color originalColor = m_SpritePtr->GetColor();
    bin::TweenEngine::Start({ .duration = 0.7f,
                              .easeType = bin::EaseType::SineOut,
                              .onUpdate =
                                  [this, originalColor, randomRotationDistance](float value)
                              {
                                  const float scale = 1.0f - value;
                                  m_SpritePtr->SetLocalScale({ scale, scale });

                                  const SDL_Color lerpColor =
                                      bin::math::Lerp(originalColor, SDL_Color{ 255, 255, 255, 255 }, value);
                                  m_SpritePtr->SetColor(lerpColor);

                                  m_SpritePtr->SetLocalAngle(value * randomRotationDistance);
                              },
                              .onEnd = [this]() { MarkForDestroy(); } },
                            *this);


    m_BoxColliderPtr->MarkForDestroy();
    m_BoxColliderPtr = nullptr;
}

void bout::Brick::OnHit(const bin::Manifold& /*unused*/) { Break(); }
