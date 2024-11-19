#include "Ball.h"

#include <BoxCollider.h>
#include <GameTime.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Physics.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "GlobalSettings.h"
#include "Trail.h"

bout::Ball::Ball()
{
    m_BoxColliderPtr = &bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.5f, 0.5f });
    m_BoxColliderPtr->SetParent(this);

    m_TrailPtr = &bin::SceneGraph::AddNode<bout::Trail>();
    m_TrailPtr->SetParent(this);
}

void bout::Ball::Update() { UpdateBallColor(); }

void bout::Ball::FixedUpdate()
{
    if(m_HoldingBall)
        return;

    MoveBall();

    constexpr float minPosition = 15.0f;
    if(GetLocalPosition().y < -minPosition)
        OnBallUnderMap();
}

void bout::Ball::Draw(const bin::Renderer& renderer)
{
    renderer.DrawBox(GetWorldPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f }, m_BallColor);
}


void bout::Ball::HoldBall() { m_HoldingBall = true; }

void bout::Ball::ShootBall()
{
    m_MoveDirection = { bin::math::RandomRange(-1.0f, 1.0f), 1 };
    m_HoldingBall = false;
}

void bout::Ball::OnHitWall()
{
    m_TimeSinceHit = 0;
    bin::MessageQueue::Broadcast(bout::MessageType::OnWallHit);
}

void bout::Ball::OnBallUnderMap() { MarkForDestroy(); }

void bout::Ball::MoveBall()
{
    // NOTE: We always normalize movement direction
    m_MoveDirection = glm::normalize(m_MoveDirection);

    constexpr float minDirection = 0.4f;

    if(m_MoveDirection.y >= 0 and m_MoveDirection.y < minDirection)
        m_MoveDirection.y = minDirection;

    if(m_MoveDirection.y < 0 and m_MoveDirection.y > -minDirection)
        m_MoveDirection.y = -minDirection;

    if(m_MoveDirection.x >= 0 and m_MoveDirection.x < minDirection)
        m_MoveDirection.x = minDirection;

    if(m_MoveDirection.x < 0 and m_MoveDirection.x > -minDirection)
        m_MoveDirection.x = -minDirection;


    constexpr float hitMoveSpeedIncreaseEffect = 13.0;
    constexpr float hitMoveSpeedIncreaseDuration = 0.4f;


    const float hitMoveSpeedIncrease =
        bin::math::Clamp01(1.0f - m_TimeSinceHit / hitMoveSpeedIncreaseDuration) * hitMoveSpeedIncreaseEffect;

    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * (m_MoveSpeed + hitMoveSpeedIncrease);
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));

    HandleBallCollision();
}

void bout::Ball::HandleBallCollision()
{
    const auto& colliders = bin::Locator::Get<Physics>().GetColliders();

    for(const auto& collider : colliders)
    {
        if(collider == m_BoxColliderPtr)
            continue;

        auto [didHit, manifold] = Physics::DoesOverlap(collider, m_BoxColliderPtr);

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
            collider->m_OnHit.Invoke();
        }
    }
}

void bout::Ball::UpdateBallColor()
{
    m_TimeSinceHit += bin::GameTime::GetDeltaTime();

    constexpr float hitTimeDuration{ 0.2f };
    constexpr SDL_Color hitColor{ 255, 0, 0, 255 };
    constexpr SDL_Color normalColor{ 200, 200, 255, 255 };

    const float colorStrength = bin::math::Clamp01(m_TimeSinceHit / hitTimeDuration);
    m_BallColor = bin::math::Lerp(hitColor, normalColor, colorStrength);
    m_TrailPtr->SetTrailColor(m_BallColor);
}
