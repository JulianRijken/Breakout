#ifndef PHYSICS_H
#define PHYSICS_H

#include <Locator.h>

#include <glm/vec2.hpp>
#include <unordered_set>

namespace bin
{
    class BoxCollider;

    struct Manifold final
    {
        glm::vec2 penetration;
        glm::ivec2 normal;
    };

    class Physics final : public bin::Service
    {
        friend class bin::BoxCollider;

    public:
        [[nodiscard]] static std::pair<bool, Manifold> DoesOverlap(bin::BoxCollider* a, bin::BoxCollider* b);
        [[nodiscard]] const std::unordered_set<bin::BoxCollider*>& GetColliders() const;

    private:
        void RegisterCollider(bin::BoxCollider* boxCollider);
        void UnregisterCollider(bin::BoxCollider* boxCollider);

        std::unordered_set<bin::BoxCollider*> m_Colliders{};
    };
}  // namespace bin


#endif  // PHYSICS_H
