#include "Ball.h"

#include <BoxCollider.h>
#include <fmt/core.h>
#include <GameTime.h>
#include <MessageQueue.h>
#include <Physics.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "Breakout.h"
#include "Trail.h"

bout::Ball::Ball()
{
    m_BoxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.5f, 0.5f });
    m_BoxColliderPtr->SetParent(this);

    const auto trailPtr = bin::SceneGraph::AddNode<bout::Trail>();
    trailPtr->SetParent(this);
}

void bout::Ball::HoldBall() { m_HoldingBall = true; }

void bout::Ball::ShootBall()
{
    m_MoveDirection = { 0, 1 };
    m_HoldingBall = false;
}

void bout::Ball::FixedUpdate()
{
    if(m_HoldingBall)
        return;

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


    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * m_MoveSpeed;
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));

    HandleBallCollision();

    if(GetLocalPosition().y < -15)
        SetLocalPosition({ 0, 0 });
}

void bout::Ball::Draw()
{
    const auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox(GetWorldPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f });
}

void bout::Ball::OnHitWall() { bin::MessageQueue::Broadcast(bout::MessageType::OnWallHit); }

void bout::Ball::HandleBallCollision()
{
    const auto& colliders = bin::Locator::Get<Physics>().GetColliders();

    for(const auto& collider : colliders)
    {
        if(collider == m_BoxColliderPtr)
            continue;

        auto [didHit, manifold] = bin::Locator::Get<Physics>().DoesOverlap(collider, m_BoxColliderPtr);

        if(didHit)
        {
            const glm::vec2 normal = glm::normalize(static_cast<glm::vec2>(manifold.normal));

            if(collider->CompareLayers(bout::layer::PADDLE))
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
