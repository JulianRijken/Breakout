#include "Paddle.h"

#include <Audio.h>
#include <GameTime.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Renderer.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Sprite.h>
#include <TweenEngine.h>

#include <algorithm>

#include "Ball.h"
#include "BoxCollider.h"
#include "GameState.h"
#include "GlobalSettings.h"

bout::Paddle::Paddle()
{
    auto& boxCollider = bin::SceneGraph::AddNode<bin::BoxCollider>(PADDLE_SIZE, bout::collisionLayer::PADDLE);
    boxCollider.SetParent(this);
    boxCollider.m_OnHit.AddListener(this, &Paddle::OnHit);

    m_SpritePtr = &bin::SceneGraph::AddNode<bin::Sprite>(IDLE_COLOR);
    m_SpritePtr->SetLocalScale(PADDLE_SIZE);
    m_SpritePtr->SetParent(this);
}

void bout::Paddle::SetPaddleTargetPosition(float targetPosition)
{
    m_PaddleTargetPosition = std::clamp(targetPosition, -MAX_MOVE_DISTANCE, MAX_MOVE_DISTANCE);
}

void bout::Paddle::HoldBall(bout::Ball& ball)
{
    assert(m_HoldingBallPtr == nullptr && "Trying to get a ball ready when there is still one");

    m_HoldingBallPtr = &ball;
    m_HoldingBallPtr->SetParent(this);
    m_HoldingBallPtr->SetLocalPosition({ 0, 1 });
}

void bout::Paddle::TryLaunchBall(Node& parent)
{
    if(not IsHoldingBall())
        return;

    m_HoldingBallPtr->SetParent(&parent);
    m_HoldingBallPtr->LaunchBall();
    m_HoldingBallPtr = nullptr;

    bin::MessageQueue::Broadcast(MessageType::BallLaunched);
}

bool bout::Paddle::IsHoldingBall() const { return m_HoldingBallPtr != nullptr; }

void bout::Paddle::FixedUpdate() { UpdatePaddlePosition(); }

void bout::Paddle::Update() { UpdatePaddleVisualAngle(); }

void bout::Paddle::OnHit(const bin::Manifold&)
{
    bin::Audio::Play(bin::Resources::GetSound(SoundName::PaddleHit));
    GameState::GetInstance().IncrementPaddleBounces();

    // Needed for the lambda capture
    bin::Sprite* spritePtrCopy = m_SpritePtr;

    // Animate paddle on hit
    bin::TweenEngine::Start({ .duration = BUMP_DURATION,
                              .onUpdate =
                                  [spritePtrCopy](float value)
                              {
                                  const float curve = bin::math::EvaluateCubicBezier(BUMP_CURVE, value).y;
                                  const SDL_Color color = bin::math::Lerp(IDLE_COLOR, HIT_COLOR, curve);

                                  spritePtrCopy->SetLocalScale(PADDLE_SIZE + HIT_SCALE_ADDITION * curve);
                                  spritePtrCopy->SetColor(color);
                              } },
                            *spritePtrCopy);
}

void bout::Paddle::UpdatePaddleVisualAngle()
{
    const float delta = GetWorldPosition().x - m_LastPosition;
    m_LastPosition = GetWorldPosition().x;

    m_PaddleAngle = bin::math::LerpSmooth(
        m_PaddleAngle, -delta * ANGLE_DISTANCE, ANGLE_SMOOTH_DURATION, bin::GameTime::GetDeltaTime());

    SetLocalAngle(m_PaddleAngle);
}

void bout::Paddle::UpdatePaddlePosition()
{
    m_PaddlePosition =
        bin::math::LerpSmooth(m_PaddlePosition, m_PaddleTargetPosition, MOVE_DURATION, bin::GameTime::GetDeltaTime());

    SetLocalPosition({ m_PaddlePosition, GetLocalPosition().y });
}
