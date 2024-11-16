#include "Trail.h"

#include <Renderer.h>

void bout::Trail::FixedUpdate()
{
    const int maxFramesBack{ 30 };

    m_PastPositions.emplace_back(GetWorldPosition());


    if(m_PastPositions.size() > maxFramesBack)
        m_PastPositions.pop_front();
}

void bout::Trail::Draw()
{
    if(m_PastPositions.empty())
        return;

    auto& renderer = bin::Locator::Get<bin::Renderer>();

    const int pointCount{ 20 };
    for(int i = 0; i < pointCount; ++i)
    {
        const float alpha = static_cast<float>(i) / static_cast<float>(pointCount - 1);
        const int index = static_cast<int>(std::round(alpha * (m_PastPositions.size() - 1)));

        const glm::vec2 drawPosition = m_PastPositions[index];
        const float scale = std::lerp(0.2f, 0.5f, alpha);
        const auto colorAlpha = static_cast<Uint8>(255 * alpha);

        renderer.DrawBox(drawPosition, { scale, scale }, { 0.5f, 0.5f }, SDL_Color{ 255, 255, 255, colorAlpha });
    }
}
