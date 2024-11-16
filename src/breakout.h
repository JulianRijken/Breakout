#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Node.h>

namespace bin
{
    class Camera;
}

namespace bout
{
    class Ball;

    class Breakout final : public bin::Node
    {
    public:
        Breakout();

        void Update() override;
        void Draw() const override;

    private:
        static constexpr float PADDLE_MOVE_DURATION = 0.1f;

        float m_GameTime{};

        float m_PaddlePosition{};
        float m_paddleTargetPostion{};

        bin::Camera* m_Camera{};
        bout::Ball* m_Ball{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
