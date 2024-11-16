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

private:
    std::unordered_set<bin::BoxCollider*> m_Colliders{};
};

#endif  // PHYSICS_H
