#include "Brick.h"

#include <Audio.h>
#include <BoxCollider.h>
#include <GameTime.h>
#include <MessageQueue.h>
#include <Renderer.h>
#include <SceneGraph.h>
#include <Shaker.h>
#include <Sprite.h>
#include <TweenEngine.h>

#include "Ball.h"
#include "GameState.h"
#include "GlobalSettings.h"
#include "Resources.h"

bout::Brick::Brick(int pointsWorth, const SDL_Color& brickColor, bool holdBall) :
    m_PointsWorth(pointsWorth),
    m_BrickColor(brickColor)
{
    m_SpritePtr = &bin::SceneGraph::AddNode<bin::Sprite>(m_BrickColor);
    m_SpritePtr->SetParent(this);

    if(holdBall)
        HoldBall();

    m_BoxColliderPtr =
        &bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 1.0f, 1.0f }, bout::collisionLayer::BRICK);
    m_BoxColliderPtr->SetParent(this);
    m_BoxColliderPtr->m_OnHit.AddListener(this, &Brick::OnHit);
}

void bout::Brick::Break()
{
    // Make sure we can't break multiple times
    if(m_BoxColliderPtr == nullptr)
        return;

    m_OnBreakEvent.Invoke(*this);
    bin::MessageQueue::Broadcast(MessageType::BrickBreak, { m_PointsWorth });
    bin::Audio::Play(bin::Resources::GetSound(SoundName::BrickBreak));

    if(m_HoldsBall)
        ReleaseBall();

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

void bout::Brick::HoldBall()
{
    if(m_HoldsBall)
        return;

    m_HoldsBall = true;

    auto& shaker = bin::SceneGraph::AddNode<bin::Shaker>(0.1f, 0.1f, 0.2f, false);
    shaker.SetParent(this);
    m_SpritePtr->SetParent(&shaker);
}

void bout::Brick::Update()
{
    if(m_HoldsBall)
        BlinkBrick();
}

void bout::Brick::BlinkBrick()
{
    constexpr SDL_Color blinkColor = { 255, 255, 255, 255 };
    constexpr float blinkSpeed = 5.0f;
    const float alpha = (std::sin(bin::GameTime::GetElapsedTime() * blinkSpeed) + 1.0f) * 0.5f;

    const SDL_Color color = bin::math::Lerp(m_BrickColor, blinkColor, alpha);
    m_SpritePtr->SetColor(color);
}

void bout::Brick::ReleaseBall()
{
    constexpr SDL_Color ballColor = { 247, 239, 0, 255 };
    constexpr SDL_Color ballHitColor = { 255, 255, 255, 255 };

    auto& ball = bin::SceneGraph::AddNode<Ball>(
        GameState::GetInstance().GetDifficultyPreset().ballMoveSpeed, ballHitColor, ballColor);
    ball.LaunchBall();
    ball.SetMoveDirection({ bin::math::RandomRange(-1.0f, 1.0f), bin::math::RandomRange(-1.0f, 1.0f) });
    ball.SetWorldPosition(GetWorldPosition());
}

void bout::Brick::OnHit(const bin::Manifold& /*unused*/) { Break(); }
