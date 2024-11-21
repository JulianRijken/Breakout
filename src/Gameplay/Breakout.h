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

    private:
        void FixedUpdate() override;
        void Update() override;

        void OnFireBallInput(const bin::InputContext& context);
        void OnCheatSpawnBallInput(const bin::InputContext& context);
        void OnCheatClearFieldInput(const bin::InputContext& context);

        void OnWallHitMessage(const bin::Message& message);
        void OnBrickBreakMessage(const bin::Message& message);

        void OnBallLostEvent();
        void OnPlayfieldClearedEvent();

        void OffsetPlayfield();
        void MovePaddle();
        void TySpawnBall();
        void ShakeCamera();
        void EndGame(bool hasWon);

        static constexpr int BRICK_BREAK_FLASH_ALPHA{ 20 };
        static constexpr float BRICK_BREAK_FLASH_DURATION{ 0.14f };
        static constexpr float CAMERA_PADDING{ 3 };

        float m_ShakeTimer{};
        bool m_GameOver{ false };
        bin::Sprite* m_BackgroundFlashSpritePtr{};
        Playfield* m_PlayfieldPtr{};
        bin::Camera* m_CameraPtr{};
        Paddle* m_PaddlePtr{};
        GameStats m_GameStats{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
