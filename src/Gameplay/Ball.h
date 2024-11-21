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
        Ball(float moveSpeed = 20.0f, SDL_Color hitColor = { 255, 0, 0, 255 },
             SDL_Color normalColor = { 200, 200, 255, 255 });

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
        float m_MoveSpeed{};
        float m_TimeSinceHit{};

        SDL_Color m_HitColor{};
        SDL_Color m_NormalColor{};
        SDL_Color m_BallColor{};

        bool m_HoldingBall{ true };
        glm::vec2 m_MoveDirection{ 1, 1 };
        bin::Trail* m_TrailPtr{};
        bin::BoxCollider* m_BoxColliderPtr{};
    };
}  // namespace bout
#endif  // BALL_H
