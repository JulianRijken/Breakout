#ifndef PADDLE_H
#define PADDLE_H

#include <Node.h>

namespace bout
{
    class Ball;

    class Paddle final : public bin::Node
    {
    public:
        Paddle();
        void SetPaddleTargetPosition(float targetPosition);

        void HoldBall(bout::Ball& ball);
        void TryLaunchBall(Node& parent);

        [[nodiscard]] bool IsHoldingBall() const;

    private:
        void FixedUpdate() override;
        void Draw(const bin::Renderer& renderer) override;


        static constexpr float MOVE_DURATION = 0.2f;
        static constexpr float MAX_MOVE_DISTANCE = 11;

        bout::Ball* m_HoldingBallPtr{};
        float m_PaddlePosition{};
        float m_PaddleTargetPosition{};
    };
}  // namespace bout


#endif  // PADDLE_H
