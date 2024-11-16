#include "Physics.h"

void Physics::RegisterCollider(bin::BoxCollider* boxCollider) { m_Colliders.insert(boxCollider); }

void Physics::UnregisterColluder(bin::BoxCollider* boxCollider) { m_Colliders.erase(boxCollider); }

bool Physics::DoesOverlap(bin::BoxCollider* a, bin::BoxCollider* b)
{
    const glm::vec2 posA = a->GetWorldPosition();
    const glm::vec2 posB = b->GetWorldPosition();
    const glm::vec2 sizeA = a->GetSize();
    const glm::vec2 sizeB = b->GetSize();

    // TODO: The boxcollider can also hold this information
    const glm::vec2 minA = posA - sizeA * 0.5f;
    const glm::vec2 maxA = posA + sizeA * 0.5f;
    const glm::vec2 minB = posB - sizeB * 0.5f;
    const glm::vec2 maxB = posB + sizeB * 0.5f;

    const bool overlapX = (minA.x <= maxB.x) and (maxA.x >= minB.x);
    const bool overlapY = (minA.y <= maxB.y) and (maxA.y >= minB.y);

    return overlapX and overlapY;
}

const std::unordered_set<bin::BoxCollider*>& Physics::GetColliders() const { return m_Colliders; }
