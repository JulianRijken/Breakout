#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Node.h>

namespace bin
{
    class Camera;
}

namespace bout
{
    class Playfield;
    class Paddle;
    class Ball;

    class Breakout final : public bin::Node
    {
    public:
        Breakout();

        void Update() override;
        void Draw() override;

    private:
        static constexpr float CAMERA_PADDING{ 3 };

        float m_GameTime{};

        bin::Camera* m_Camera{};
        bout::Playfield* m_PlayfieldPtr{};
        bout::Paddle* m_PaddlePtr{};
        bout::Ball* m_BallPtr{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
