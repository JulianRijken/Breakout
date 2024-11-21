#include "Ball.h"

#include <BoxCollider.h>
#include <GameTime.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Physics.h>
#include <Renderer.h>
#include <Resources.h>
#include <SceneGraph.h>

#include "GlobalSettings.h"
#include "Trail.h"

bout::Ball::Ball(float moveSpeed, SDL_Color hitColor, SDL_Color normalColor) :
    m_MoveSpeed(moveSpeed),
    m_HitColor(hitColor),
    m_NormalColor(normalColor)
{
    m_BoxColliderPtr = &bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.5f, 0.5f });
    m_BoxColliderPtr->SetParent(this);

    m_TrailPtr = &bin::SceneGraph::AddNode<bin::Trail>();
    m_TrailPtr->SetParent(this);
}

void bout::Ball::Update() { UpdateBallColor(); }

void bout::Ball::FixedUpdate()
{
    if(m_HoldingBall)
        return;

    MoveBall();

    // Should probably be something breakout handles and not the ball
    constexpr float minPosition = 18.0f;
    if(GetLocalPosition().y < -minPosition)
        OnBallUnderMap();
}

void bout::Ball::Draw(const bin::Renderer& renderer)
{
    renderer.DrawRect(GetWorldPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f }, m_BallColor);
}


void bout::Ball::HoldBall() { m_HoldingBall = true; }

void bout::Ball::LaunchBall()
{
    m_MoveDirection = { 0.0f, 1.0f };
    m_HoldingBall = false;
}

void bout::Ball::OnHitWall()
{
    m_TimeSinceHit = 0;
    bin::MessageQueue::Broadcast(bout::MessageType::BallCollided);
}

void bout::Ball::OnBallUnderMap()
{
    m_OnBallLostEvent.Invoke();
    MarkForDestroy();
}

void bout::Ball::MoveBall()
{
    // NOTE: We always normalize movement direction
    m_MoveDirection = glm::normalize(m_MoveDirection);

    constexpr float minDirection = 0.4f;

    if(m_MoveDirection.y >= 0 and m_MoveDirection.y < minDirection)
        m_MoveDirection.y = minDirection;

    if(m_MoveDirection.y < 0 and m_MoveDirection.y > -minDirection)
        m_MoveDirection.y = -minDirection;


    constexpr float hitMoveSpeedIncreaseEffect = 13.0f;
    constexpr float hitMoveSpeedIncreaseDuration = 0.4f;


    const float hitMoveSpeedIncrease =
        bin::math::Clamp01(1.0f - m_TimeSinceHit / hitMoveSpeedIncreaseDuration) * hitMoveSpeedIncreaseEffect;

    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * (m_MoveSpeed + hitMoveSpeedIncrease);
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));

    HandleBallCollision();
}

void bout::Ball::HandleBallCollision()
{
    const auto& colliders = bin::Locator::Get<bin::Physics>().GetColliders();

    for(const auto& collider : colliders)
    {
        if(collider == m_BoxColliderPtr)
            continue;

        auto [didHit, manifold] = bin::Physics::DoesOverlap(collider, m_BoxColliderPtr);

        if(didHit)
        {
            const glm::vec2 normal = glm::normalize(static_cast<glm::vec2>(manifold.normal));

            if(collider->CompareLayers(bout::collisionLayer::PADDLE))
            {
                const glm::vec2 paddleDirection = GetWorldPosition() - collider->GetWorldPosition();
                m_MoveDirection = paddleDirection;
            }
            else
            {
                // Reflection formula w = v - 2 * dot(v, n)
                const glm::vec2 normalizedDirection = glm::normalize(m_MoveDirection);
                const glm::vec2 reflectedDirection =
                    normalizedDirection - 2.0f * glm::dot(normalizedDirection, normal) * normal;

                m_MoveDirection = reflectedDirection;
            }

            Translate(-(normal * manifold.penetration));
            OnHitWall();
            collider->m_OnHit.Invoke(manifold);
        }
    }
}

void bout::Ball::UpdateBallColor()
{
    m_TimeSinceHit += bin::GameTime::GetDeltaTime();

    constexpr float hitTimeDuration{ 0.2f };

    const float colorStrength = bin::math::Clamp01(m_TimeSinceHit / hitTimeDuration);
    m_BallColor = bin::math::Lerp(m_HitColor, m_NormalColor, colorStrength);
    m_TrailPtr->SetTrailColor(m_BallColor);
}
