#ifndef BALL_H
#define BALL_H

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
        Ball();

    private:
        void FixedUpdate() override;
        void Draw() override;

        // In Units a second
        float m_MoveSpeed{ 7.0 };

        glm::ivec2 m_MoveDirection{ 1, 1 };
        bin::BoxCollider* m_BoxColliderPtr{};
    };
}  // namespace bout

#endif  // BALL_H
