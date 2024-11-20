#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Node.h>

#include "GameStats.h"


namespace bin
{
    class Sprite;
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
        void OnFireBallInput(const bin::InputContext& context);

        void OnWallHitMessage(const bin::Message& message);
        void OnBrickBreakMessage(const bin::Message& message);

        void OnBallLostEvent();
        void OnPlayfieldClearedEvent();

        void TySpawnBall();
        void ShakeCamera();

        void OnGameOver();

        static constexpr int BRICK_BREAK_FLASH_ALPHA{ 20 };
        static constexpr float BRICK_BREAK_FLASH_DURATION{ 0.14f };

        static constexpr float CAMERA_PADDING{ 3 };
        float m_ShakeTimer{};

        bin::Camera* m_CameraPtr{};
        Playfield* m_PlayfieldPtr{};
        Paddle* m_PaddlePtr{};
        bin::Sprite* m_BackgroundFlashSpritePtr{};
        GameStats m_GameStats{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
