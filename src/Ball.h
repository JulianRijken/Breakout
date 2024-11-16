#ifndef BALL_H
#define BALL_H

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
        void FixedUpdate() override;
        void Draw() override;

        void OnHitWall();

        void HandleBallCollision();

        // In Units a second
        float m_MoveSpeed{ 15.0 };

        bool m_HoldingBall{ true };
        glm::vec2 m_MoveDirection{ 1, 1 };
        bin::BoxCollider* m_BoxColliderPtr{};
    };
}  // namespace bout
#endif  // BALL_H
