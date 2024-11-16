#include "Ball.h"

#include <BoxCollider.h>
#include <fmt/core.h>
#include <GameTime.h>
#include <Physics.h>
#include <Renderer.h>
#include <SceneGraph.h>

bout::Ball::Ball()
{
    m_BoxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.5f, 0.5f });
    m_BoxColliderPtr->SetParent(this);
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


    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * m_MoveSpeed;
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));

    HandleBallCollision();

    if(GetLocalPosition().y < -15)
        SetLocalPosition({ 0, 0 });
}

void bout::Ball::Draw()
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox(GetWorldPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f });
}

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
            // Reflection formula w = v - 2 * dot(v, n)
            const glm::vec2 normal = glm::normalize(static_cast<glm::vec2>(manifold.normal));
            const glm::vec2 normalizedDirection = glm::normalize(m_MoveDirection);
            const glm::vec2 reflectedDirection =
                normalizedDirection - 2.0f * glm::dot(normalizedDirection, normal) * normal;

            m_MoveDirection = glm::round(reflectedDirection);
            Translate(-(normal * manifold.penetration));
        }
    }
}
