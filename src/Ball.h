#ifndef BALL_H
#define BALL_H

#include <SDL_pixels.h>
#include <Trail.h>

#include "Node.h"

namespace bin
{
    class BoxCollider;
}

namespace bout
{
    class Ball final : public bin::Node
    {
    public:
        Ball();

        void HoldBall();
        void ShootBall();

    private:
        void Update() override;
        void FixedUpdate() override;
        void Draw(const bin::Renderer& renderer) override;

        void OnHitWall();
        void OnBallUnderMap();

        void MoveBall();
        void HandleBallCollision();
        void UpdateBallColor();

        // In Units a second
        float m_MoveSpeed{ 20.0 };
        float m_TimeSinceHit{ 0.0f };

        bool m_HoldingBall{ true };
        bout::Trail* m_TrailPtr{};
        glm::vec2 m_MoveDirection{ 1, 1 };
        bin::BoxCollider* m_BoxColliderPtr{};
        SDL_Color m_BallCollor{};
    };
}  // namespace bout
#endif  // BALL_H
