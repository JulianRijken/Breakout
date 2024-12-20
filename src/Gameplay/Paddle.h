#ifndef PADDLE_H
#define PADDLE_H

#include <Node.h>
#include <SDL_pixels.h>

namespace bin
{
    struct Manifold;
    class Sprite;
}  // namespace bin

namespace bout
{
    class Ball;

    class Paddle final : public bin::Node, public bin::IEventListener
    {
    public:
        Paddle();

        ~Paddle() override = default;
        Paddle(Paddle&&) = delete;
        Paddle(const Paddle&) = delete;
        Paddle& operator=(Paddle&&) = delete;
        Paddle& operator=(const Paddle&) = delete;

        void SetPaddleTargetPosition(float targetPosition);

        void HoldBall(bout::Ball& ball);
        void TryLaunchBall(Node& parent);

        [[nodiscard]] bool IsHoldingBall() const;

    private:
        void FixedUpdate() override;
        void Update() override;
        void OnHit(const bin::Manifold& /*unused*/);

        void UpdatePaddleVisualAngle();
        void UpdatePaddlePosition();

        static constexpr glm::vec2 PADDLE_SIZE = { 2.5f, 0.6f };
        static constexpr float MOVE_DURATION = 0.2f;
        static constexpr float MAX_MOVE_DISTANCE = 12 - PADDLE_SIZE.x / 2.0f;

        static constexpr float ANGLE_SMOOTH_DURATION = 0.3f;
        static constexpr float ANGLE_DISTANCE = 30.0f;
        static constexpr float BUMP_DURATION = 0.3f;
        static constexpr float BUMP_HEIGHT = 0.4f;

        static constexpr SDL_Color IDLE_COLOR = { 200, 200, 220, 240 };
        static constexpr SDL_Color HIT_COLOR = { 255, 255, 255, 255 };
        static constexpr glm::vec2 HIT_SCALE_ADDITION = { 0.65f, -0.3f };


        bout::Ball* m_HoldingBallPtr{};
        bin::Sprite* m_SpritePtr{};
        float m_PaddlePosition{};
        float m_PaddleTargetPosition{};

        // Paddle rotation smoothing
        float m_LastPosition{};
        float m_PaddleAngle{};
    };
}  // namespace bout


#endif  // PADDLE_H
