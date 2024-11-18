#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Node.h>

#include "GameStats.h"


namespace bin
{
    struct InputContext;
    struct Message;
    class Camera;
}

namespace bout
{
    class Playfield;
    class Paddle;
    class Ball;

    class Breakout final : public bin::Node, public bin::IEventListener
    {
    public:
        Breakout();
        ~Breakout() override;

        void FixedUpdate() override;
        void Update() override;

        void OnWallHitMessage(const bin::Message& message);
        void ShakeCamera();

    private:
        void OnFireBallInput(const bin::InputContext& context);
        void OnForceRestartInput(const bin::InputContext& context);

        static constexpr float CAMERA_PADDING{ 2 };
        float m_ShakeTimer{};

        bin::Camera* m_CameraPtr{};
        Playfield* m_PlayfieldPtr{};
        Paddle* m_PaddlePtr{};
        GameStats m_GameStats{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
