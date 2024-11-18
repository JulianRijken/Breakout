#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <Event.h>
#include <Node.h>

#include <glm/vec2.hpp>

namespace bin
{
    class BoxCollider final : public bin::Node
    {
    public:
        BoxCollider(const glm::vec2& size, uint16_t layers = 0x0001);
        ~BoxCollider() override;

        BoxCollider(BoxCollider&&) = delete;
        BoxCollider(const BoxCollider&) = delete;
        BoxCollider& operator=(BoxCollider&&) = delete;
        BoxCollider& operator=(const BoxCollider&) = delete;

        [[nodiscard]] const glm::vec2& GetSize() const;

        bool CompareLayers(uint16_t layers) const;

        bin::Event<> m_OnHit{};

    private:
        void Draw(const bin::Renderer& renderer) override;

        uint16_t m_Layers;
        glm::vec2 m_Size;
    };

}  // namespace bin


#endif  // BOXCOLLIDER_H
