#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <Event.h>
#include <Node.h>

#include <glm/vec2.hpp>

namespace bin
{

    struct Manifold;

    class BoxCollider final : public bin::Node
    {
    public:
        BoxCollider(const glm::vec2& size = { 1.0f, 1.0f }, uint16_t layers = 0x0001);
        ~BoxCollider() override;

        BoxCollider(BoxCollider&&) = delete;
        BoxCollider(const BoxCollider&) = delete;
        BoxCollider& operator=(BoxCollider&&) = delete;
        BoxCollider& operator=(const BoxCollider&) = delete;

        [[nodiscard]] glm::vec2 GetSize();

        bool CompareLayers(uint16_t layers) const;

        bin::Event<const Manifold&> m_OnHit{};

    private:
        void Draw(const bin::Renderer& renderer) override;

        uint16_t m_Layers{ 0x0001 };
        glm::vec2 m_Size{ 1.0f, 1.0f };
    };

}  // namespace bin


#endif  // BOXCOLLIDER_H
