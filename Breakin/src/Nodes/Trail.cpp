#include "Trail.h"

#include <MathExtensions.h>
#include <Renderer.h>

void bin::Trail::SetTrailColor(const SDL_Color& newColor) { m_TrailColor = newColor; }

void bin::Trail::FixedUpdate() { IncrementPastPoints(); }

void bin::Trail::Draw(const bin::Renderer& renderer)
{
    if(m_PastPoints.empty())
        return;

    constexpr int particleCount{ 20 };

    for(int i = 0; i < particleCount; ++i)
    {
        // Alpha is 0 - 1 over the length of the tail
        const float alpha = bin::math::Clamp01(static_cast<float>(i) / static_cast<float>(particleCount - 1));
        const int index = static_cast<int>(std::round(alpha * (m_PastPoints.size() - 1)));

        const glm::vec2 drawPosition = m_PastPoints[index].first;

        const SDL_Color drawColor = m_PastPoints[index].second;
        const float scale = std::lerp(0.2f, 0.5f, alpha);
        const auto colorAlpha = static_cast<Uint8>(255 * alpha);

        renderer.DrawRect(drawPosition,
                          { scale, scale },
                          { 0.5f, 0.5f },
                          SDL_Color{ drawColor.r, drawColor.g, drawColor.b, colorAlpha });
    }
}

void bin::Trail::IncrementPastPoints()
{
    // Needs to be done in fixed update because this allows for equal spacing
    // could be solved with more math
    constexpr int maxFramesBack{ 30 };

    m_PastPoints.emplace_back(GetWorldPosition(), m_TrailColor);

    if(m_PastPoints.size() > maxFramesBack)
        m_PastPoints.pop_front();
}
