#ifndef PADDLE_H
#define PADDLE_H

#include <Node.h>

namespace bout
{
    class Paddle final : public bin::Node
    {
    public:
        Paddle();
        void SetPaddleTargetPosition(float targetPosition);

    private:
        void FixedUpdate() override;
        void Draw() override;

        static constexpr float MOVE_DURATION = 0.1f;
        static constexpr float MAX_MOVE_DISTANCE = 11;

        float m_PaddlePosition{};
        float m_PaddleTargetPosition{};
    };
}  // namespace bout


#endif  // PADDLE_H
