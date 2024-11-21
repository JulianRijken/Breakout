#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <Event.h>
#include <Node.h>

#include <glm/vec2.hpp>

namespace bin
{
    struct Manifold;

    class BoxCollider final : public Node
    {
    public:
        BoxCollider(const glm::vec2& size = { 1.0f, 1.0f }, uint16_t layers = 0x0001);
        ~BoxCollider() override;

        BoxCollider(BoxCollider&&) = delete;
        BoxCollider(const BoxCollider&) = delete;
        BoxCollider& operator=(BoxCollider&&) = delete;
        BoxCollider& operator=(const BoxCollider&) = delete;

        [[nodiscard]] glm::vec2 GetSize() const;

        bool CompareLayers(uint16_t layers) const;

        Event<const Manifold&> m_OnHit{};

    private:
        uint16_t m_Layers{ 0x0001 };
        glm::vec2 m_Size{ 1.0f, 1.0f };
    };

}  // namespace bin

#endif  // BOXCOLLIDER_H
