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

        ~Ball() override = default;
        Ball(Ball&&) = delete;
        Ball(const Ball&) = delete;
        Ball& operator=(Ball&&) = delete;
        Ball& operator=(const Ball&) = delete;

        void HoldBall();
        void LaunchBall();

        bin::Event<> m_OnBallLostEvent{};

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
        float m_MoveSpeed{ 20.0f };
        float m_TimeSinceHit{ 0.0f };

        bool m_HoldingBall{ true };
        SDL_Color m_BallColor{};
        glm::vec2 m_MoveDirection{ 1, 1 };
        bin::Trail* m_TrailPtr{};
        bin::BoxCollider* m_BoxColliderPtr{};
    };
}  // namespace bout
#endif  // BALL_H
