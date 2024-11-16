#ifndef BALL_H
#define BALL_H

#include "Node.h"

namespace bout
{
    class Ball final : public bin::Node
    {
    private:
        void FixedUpdate() override;
        void Draw() const override;

        // In Units a second
        float m_MoveSpeed{ 1.0 };

        glm::ivec2 m_MoveDirection{ 1, 1 };
    };
}  // namespace bout

#endif  // BALL_H
