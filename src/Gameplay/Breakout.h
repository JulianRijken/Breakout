#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Node.h>

namespace bin
{
    class Shaker;
    class Sprite;
    class Camera;
    struct InputContext;
    struct Message;
}  // namespace bin

namespace bout
{
    class PauseMenu;
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

        void OnFireBallInput(const bin::InputContext& context);
        void OnCheatSpawnBallInput(const bin::InputContext& context);
        void OnCheatClearFieldInput(const bin::InputContext& context);
        void OnPauseGameInput(const bin::InputContext& context);

        void OnWallHitMessage(const bin::Message& message);
        void OnBrickBreakMessage(const bin::Message& message);
        void OnFieldClearOfBallsMessage(const bin::Message& message);

        void OnPlayfieldClearedEvent();

        void OffsetPlayfield();
        void MovePaddle();
        void TrySpawnBall();
        void EndGame(bool hasWon);
        void FlashScreen();

        static constexpr int BRICK_BREAK_FLASH_ALPHA{ 20 };
        static constexpr float BRICK_BREAK_FLASH_DURATION{ 0.14f };
        static constexpr float CAMERA_PADDING{ 3 };

        bool m_GameOver{ false };

        bout::PauseMenu* m_PauseMenuPtr{};
        bout::Playfield* m_PlayfieldPtr{};
        bout::Paddle* m_PaddlePtr{};

        bin::Shaker* m_CameraShakerPtr{};
        bin::Camera* m_CameraPtr{};
        bin::Sprite* m_BackgroundFlashSpritePtr{};
    };

}  // namespace bout
#endif  // BREAKOUT_H
