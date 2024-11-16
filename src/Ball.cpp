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

void bout::Ball::FixedUpdate()
{
    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * m_MoveSpeed;
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));


    auto& colliders = bin::Locator::Get<Physics>().GetColliders();


    for(const auto& collider : colliders)
    {
        if(collider == m_BoxColliderPtr)
            continue;

        bool overlap = bin::Locator::Get<Physics>().DoesOverlap(collider, m_BoxColliderPtr);

        if(overlap)
        {
            const glm::vec2 dir = collider->GetWorldPosition() - GetWorldPosition();

            if(dir.y > 0)
                m_MoveDirection.y = -1;

            if(dir.y < 0)
                m_MoveDirection.y = 1;

            if(dir.x > 0)
                m_MoveDirection.x = -1;

            if(dir.x < 0)
                m_MoveDirection.x = 1;
        }
    }
}

void bout::Ball::Draw()
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox(GetLocalPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f });
}
