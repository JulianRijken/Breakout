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

        [[nodiscard]] const glm::vec2& GetSize();

        bin::Event<> m_OnHit{};

        bool CompareLayers(uint16_t layers) const;

    private:
        void Draw() override;

        uint16_t m_Layers;
        glm::vec2 m_Size;
    };

}  // namespace bin


#endif  // BOXCOLLIDER_H
