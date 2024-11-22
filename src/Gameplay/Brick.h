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
}  // namespace bin

namespace bout
{
    class Brick final : public bin::Node, public bin::IEventListener
    {
    public:
        Brick(int pointsWorth, const SDL_Color& brickColor, bool holdBall = false);

        ~Brick() override = default;
        Brick(Brick&&) = delete;
        Brick(const Brick&) = delete;
        Brick& operator=(Brick&&) = delete;
        Brick& operator=(const Brick&) = delete;

        void Break();
        void HoldBall();

        bin::Event<Brick&> m_OnBreakEvent{};

    private:
        void Update() override;

        void Blink();
        void ReleaseBall();
        void OnHit(const bin::Manifold& manifold);

        int m_PointsWorth{ 0 };
        bool m_HoldsBall{ false };
        SDL_Color m_BrickColor{};
        bin::BoxCollider* m_BoxColliderPtr{};
        bin::Sprite* m_SpritePtr{};
    };
}  // namespace bout

#endif  // BRICK_H
