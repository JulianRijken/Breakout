#ifndef PHYSICS_H
#define PHYSICS_H

#include <Locator.h>
#include <unordered_set>

#include "BoxCollider.h"

struct Manifold
{
    glm::vec2 penetration;
    glm::ivec2 normal;
};

class Physics final : public bin::Service
{
public:
    void RegisterCollider(bin::BoxCollider* boxCollider);
    void UnregisterCollider(bin::BoxCollider* boxCollider);

    [[nodiscard]] std::pair<bool, Manifold> DoesOverlap(bin::BoxCollider* a, bin::BoxCollider* b);
    [[nodiscard]] const std::unordered_set<bin::BoxCollider*>& GetColliders() const;

private:
    std::unordered_set<bin::BoxCollider*> m_Colliders{};
};

#endif  // PHYSICS_H
