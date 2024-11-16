#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "Node.h"

namespace jul
{
    class Breakout final : public Node
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
    };

}  // namespace jul
#endif  // BREAKOUT_H
