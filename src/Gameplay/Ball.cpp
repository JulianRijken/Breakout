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

bout::Ball::Ball(float moveSpeed, const SDL_Color& hitColor, const SDL_Color& normalColor) :
    m_MoveSpeed(moveSpeed),
    m_HitColor(hitColor),
    m_NormalColor(normalColor)
{
    m_BoxColliderPtr = &bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.5f, 0.5f });
    m_BoxColliderPtr->SetParent(this);

    m_TrailPtr = &bin::SceneGraph::AddNode<bin::Trail>();
    m_TrailPtr->SetParent(this);

    bin::MessageQueue::Broadcast(MessageType::BallSpawned);
}

void bout::Ball::Update() { UpdateColor(); }

void bout::Ball::FixedUpdate()
{
    if(m_Locked)
        return;

    Move();

    // HACK: Should probably be something breakout handles and not the ball
    constexpr float minPosition = 18.0f;
    if(GetLocalPosition().y < -minPosition)
        OnBallUnderMap();
}

void bout::Ball::Draw(const bin::Renderer& renderer)
{
    renderer.DrawRect(GetWorldPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f }, m_Color);
}

void bout::Ball::Lock() { m_Locked = true; }

void bout::Ball::Launch()
{
    m_MoveDirection = { 0.0f, 1.0f };
    m_Locked = false;
}

void bout::Ball::SetMoveDirection(const glm::vec2& moveDirection) { m_MoveDirection = moveDirection; }

void bout::Ball::OnHitWall()
{
    m_TimeSinceHit = 0;
    bin::MessageQueue::Broadcast(bout::MessageType::BallCollided);
}

void bout::Ball::OnBallUnderMap()
{
    if(IsMarkedForDestroy())
        return;

    bin::MessageQueue::Broadcast(MessageType::BallLost);
    MarkForDestroy();
}

void bout::Ball::Move()
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

    const glm::vec2 velocity = m_MoveDirection * (m_MoveSpeed + hitMoveSpeedIncrease);
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));

    HandleCollision();
}

void bout::Ball::HandleCollision()
{
    const auto& colliders = bin::Locator::Get<bin::Physics>().GetColliders();

    for(const auto& collider : colliders)
    {
        if(collider == m_BoxColliderPtr)
            continue;

        auto hit = bin::Physics::DoesOverlap(collider, m_BoxColliderPtr);

        if(hit.has_value())
        {
            const auto& manifold{ hit.value() };

            const glm::vec2 normal = manifold.normal;

            if(collider->CompareLayers(bout::collisionLayer::PADDLE))
            {
                m_MoveDirection = GetWorldPosition() - collider->GetWorldPosition();
            }
            else
            {
                // Reflection formula w = v - 2 * dot(v, n)
                m_MoveDirection -= 2.0f * glm::dot(m_MoveDirection, normal) * normal;
            }

            Translate(-normal * manifold.penetration);
            OnHitWall();
            collider->m_OnHit.Invoke(manifold);
        }
    }
}

void bout::Ball::UpdateColor()
{
    m_TimeSinceHit += bin::GameTime::GetDeltaTime();

    constexpr float hitTimeDuration{ 0.2f };

    const float colorStrength = bin::math::Clamp01(m_TimeSinceHit / hitTimeDuration);
    m_Color = bin::math::Lerp(m_HitColor, m_NormalColor, colorStrength);
    m_TrailPtr->SetTrailColor(m_Color);
}
