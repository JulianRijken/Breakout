#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <Node.h>

#include <glm/vec2.hpp>

namespace bin
{
    class BoxCollider final : public bin::Node
    {
    public:
        BoxCollider(const glm::vec2& size);
        ~BoxCollider() override;

        [[nodiscard]] const glm::vec2& GetSize();

    private:
        void Draw() override;

        glm::vec2 m_Size{ 0.8f, 0.8f };
    };

}  // namespace bin


#endif  // BOXCOLLIDER_H
