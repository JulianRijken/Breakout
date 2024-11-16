#include "Ball.h"

#include <fmt/core.h>
#include <GameTime.h>

#include "Renderer.h"


void bout::Ball::FixedUpdate()
{
    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * m_MoveSpeed;
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));


    if(GetLocalPosition().x > 2 and m_MoveDirection.x > 0)
        m_MoveDirection.x *= -1;

    if(GetLocalPosition().x < -2 and m_MoveDirection.x < 0)
        m_MoveDirection.x *= -1;
}

void bout::Ball::Draw()
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox(GetLocalPosition(), { 0.5f, 0.5f }, { 0.5f, 0.5f });
}
