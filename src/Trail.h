#ifndef TRAIL_H
#define TRAIL_H

#include <Node.h>

#include <deque>

namespace bout
{
    class Trail final : public bin::Node
    {
    private:
        void FixedUpdate() override;
        void Draw() override;


        std::deque<glm::vec2> m_PastPositions{};
    };
}  // namespace bin

#endif  // TRAIL_H
