#include "Ball.h"

#include <GameTime.h>

#include "Renderer.h"


void bout::Ball::FixedUpdate()
{
    const glm::vec2 velocity = static_cast<glm::vec2>(m_MoveDirection) * m_MoveSpeed;
    Translate(velocity * static_cast<float>(bin::GameTime::GetFixedDeltaTime()));

    if(GetLocalPosition().x > 0 and m_MoveDirection.x > 0)
        m_MoveDirection.x *= 1;
}

void bout::Ball::Draw() const
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox(GetLocalPosition(), { 1, 1 }, { 0.5f, 0.5f });
}
