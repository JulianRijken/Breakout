#ifndef BREAKOUT_H
#define BREAKOUT_H

namespace jul
{
    class Breakout final
    {
    public:
        void Update();
        void Draw() const;

    private:
        static constexpr float PADDLE_MOVE_DURATION = 0.1f;

        float m_GameTime{};

        float m_PaddlePosition{};
        float m_paddleTargetPostion{};
    };

}  // namespace jul
#endif  // BREAKOUT_H
