#ifndef BALL_H
#define BALL_H

#include <SDL_pixels.h>
#include <Trail.h>

#include "Node.h"

namespace bin
{
    class BoxCollider;
}

namespace bout
{
    class Ball final : public bin::Node
    {
    public:
        Ball(float moveSpeed = 20.0f, const SDL_Color& hitColor = { 255, 0, 0, 255 },
             const SDL_Color& normalColor = { 200, 200, 255, 255 });

        ~Ball() override = default;
        Ball(Ball&&) = delete;
        Ball(const Ball&) = delete;
        Ball& operator=(Ball&&) = delete;
        Ball& operator=(const Ball&) = delete;

        void Lock();
        void Launch();
        void SetMoveDirection(const glm::vec2& moveDirection);

    private:
        void Update() override;
        void FixedUpdate() override;
        void Draw(const bin::Renderer& renderer) override;

        void OnHitWall();
        void OnBallUnderMap();

        void Move();
        void HandleCollision();
        void UpdateColor();

        // In Units a second
        float m_MoveSpeed{};
        float m_TimeSinceHit{};

        SDL_Color m_HitColor{};
        SDL_Color m_NormalColor{};
        SDL_Color m_Color{};

        bool m_Locked{ true };
        glm::vec2 m_MoveDirection{ 1, 1 };
        bin::Trail* m_TrailPtr{};
        bin::BoxCollider* m_BoxColliderPtr{};
    };
}  // namespace bout
#endif  // BALL_H
