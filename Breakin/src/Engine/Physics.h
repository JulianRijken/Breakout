#ifndef PHYSICS_H
#define PHYSICS_H

#include <Locator.h>

#include <unordered_set>

#include "BoxCollider.h"

class Physics : public bin::Service
{
public:
    void RegisterCollider(bin::BoxCollider* boxCollider);
    void UnregisterColluder(bin::BoxCollider* boxCollider);

    [[nodiscard]] bool DoesOverlap(bin::BoxCollider* a, bin::BoxCollider* b);

    [[nodiscard]] const std::unordered_set<bin::BoxCollider*>& GetColliders() const;

private:
    std::unordered_set<bin::BoxCollider*> m_Colliders{};
};

#endif  // PHYSICS_H
