#ifndef BRICK_H
#define BRICK_H

#include <Event.h>
#include <Node.h>
#include <SDL_pixels.h>

namespace bin
{
    class BoxCollider;
    class Sprite;
    struct Manifold;
}

namespace bout
{
    class Brick final : public bin::Node, public bin::IEventListener
    {
    public:
        Brick(int pointsWorth, const SDL_Color& brickColor);

        ~Brick() override = default;
        Brick(Brick&&) = delete;
        Brick(const Brick&) = delete;
        Brick& operator=(Brick&&) = delete;
        Brick& operator=(const Brick&) = delete;

        void Break();

    private:
        void OnHit(const bin::Manifold& manifold);

        int m_PointsWorth{ 0 };
        bin::BoxCollider* m_BoxColliderPtr{};
        bin::Sprite* m_SpritePtr{};
    };
}  // namespace bout

#endif  // BRICK_H
