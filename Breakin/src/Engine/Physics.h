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

    class Physics final : public Service
    {
        // Allow the box collider to register and unregister itself
        friend class BoxCollider;

    public:
        [[nodiscard]] static std::pair<bool, Manifold> DoesOverlap(BoxCollider* a, BoxCollider* b);
        [[nodiscard]] const std::unordered_set<BoxCollider*>& GetColliders() const;

    private:
        void RegisterCollider(BoxCollider* boxCollider);
        void UnregisterCollider(BoxCollider* boxCollider);

        std::unordered_set<BoxCollider*> m_Colliders{};
    };
}  // namespace bin


#endif  // PHYSICS_H
