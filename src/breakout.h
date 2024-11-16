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

    class Breakout final : public bin::Node
    {
    public:
        Breakout();

        void FixedUpdate() override;
        void Update() override;
        void Draw() override;

        void ShakeCamera();

    private:
        static constexpr float CAMERA_PADDING{ 2 };

        float m_GameTime{};

        float m_ShakeTimer{};

        bin::Camera* m_Camera{};
        bout::Playfield* m_PlayfieldPtr{};
        bout::Paddle* m_PaddlePtr{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
