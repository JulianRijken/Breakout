#ifndef BRICK_H
#define BRICK_H

#include <Event.h>
#include <Node.h>
#include <SDL_pixels.h>

namespace bin
{
    class Manifold;
}

namespace bout
{
    class Brick final : public bin::Node, public bin::IEventListener
    {
    public:
        Brick(int pointsWorth, const glm::vec2& brickSize, const SDL_Color& brickColor);

        void Break();

    private:
        void Draw(const bin::Renderer& renderer) override;
        void OnHit(const bin::Manifold& manifold);

        int m_PointsWorth{ 0 };
        bool m_Broken{ false };
        glm::vec2 m_BrickSize{ 1, 1 };
        SDL_Color m_BrickColor{ 255, 255, 255, 255 };
    };
}  // namespace bout

#endif  // BRICK_H
