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

        Breakout(Breakout&&) = delete;
        Breakout(const Breakout&) = delete;
        Breakout& operator=(Breakout&&) = delete;
        Breakout& operator=(const Breakout&) = delete;

        void FixedUpdate() override;
        void Update() override;

    private:
        void ShakeCamera();
        void OnWallHitMessage(const bin::Message& message);
        void OnFireBallInput(const bin::InputContext& context);
        void OnForceRestartInput(const bin::InputContext& context);
        void OnPlayfieldClearedEvent();

        static constexpr float CAMERA_PADDING{ 2 };
        float m_ShakeTimer{};

        bin::Camera* m_CameraPtr{};
        Playfield* m_PlayfieldPtr{};
        Paddle* m_PaddlePtr{};
        GameStats m_GameStats{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
