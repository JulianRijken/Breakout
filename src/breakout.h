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
    enum class MessageType
    {
        OnWallHit,
        OnPaddleHit,

        // arg[0] = int pointsWorth
        OnBrickBreak,

        // arg[0] = int score
        OnScoreChange
    };

    enum class InputActionName
    {
        FireBall
    };

    namespace collisionLayer
    {
        constexpr uint16_t Index(int index) { return 1 << index; }
        constexpr uint16_t ALL = 0xFFFF;
        constexpr uint16_t BRICK = Index(1);
        constexpr uint16_t PADDLE = Index(2);
    }  // namespace layer


    class Playfield;
    class Paddle;

    class Breakout final : public bin::Node, public bin::IEventListener
    {
    public:
        Breakout();

        void FixedUpdate() override;
        void Update() override;

        void OnWallHitMessage(const bin::Message& message);
        void ShakeCamera();

    private:
        void OnFireBallInput(const bin::InputContext& context);

        static constexpr float CAMERA_PADDING{ 2 };
        float m_ShakeTimer{};

        bin::Camera* m_CameraPtr{};
        Playfield* m_PlayfieldPtr{};
        Paddle* m_PaddlePtr{};
        GameStats m_GameStats{};
    };

}  // namespace bin
#endif  // BREAKOUT_H
