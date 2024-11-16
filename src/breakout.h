#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Node.h>

namespace bin
{
    struct Message;
    class Camera;
}

namespace bout
{

    enum class MessageType
    {
        OnWallHit,
    };

    namespace layer
    {
        constexpr uint16_t Index(int index) { return 1 << index; }
        constexpr uint16_t ALL = 0xFFFF;
        constexpr uint16_t BRICK = Index(1);
        constexpr uint16_t PADDLE = Index(2);
    }  // namespace layer


    class Playfield;
    class Paddle;

    class Breakout final : public bin::Node
    {
    public:
        Breakout();

        void FixedUpdate() override;
        void Update() override;
        void Draw() override;

        void OnWallHitMessage(const bin::Message& message);
        void ShakeCamera();

    private:
        static constexpr float CAMERA_PADDING{ 2 };

        float m_ShakeTimer{};

        bin::Camera* m_Camera{};
        bout::Playfield* m_PlayfieldPtr{};
        bout::Paddle* m_PaddlePtr{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
