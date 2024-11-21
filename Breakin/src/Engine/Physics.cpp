#include "Physics.h"

#include <BoxCollider.h>

#include <glm/common.hpp>

#include "MathExtensions.h"

void bin::Physics::RegisterCollider(bin::BoxCollider* boxCollider) { m_Colliders.insert(boxCollider); }

void bin::Physics::UnregisterCollider(bin::BoxCollider* boxCollider) { m_Colliders.erase(boxCollider); }

std::pair<bool, bin::Manifold> bin::Physics::DoesOverlap(bin::BoxCollider* a, bin::BoxCollider* b)
{
    // Overlap function based on c2AABBtoAABB from cute_c2
    // https://github.com/RandyGaul/cute_headers/blob/master/cute_c2.h

    const glm::vec2 posA = a->GetWorldPosition();
    const glm::vec2 posB = b->GetWorldPosition();
    const glm::vec2 sizeA = a->GetSize();
    const glm::vec2 sizeB = b->GetSize();

    const glm::vec2 minA = posA - sizeA * 0.5f;
    const glm::vec2 maxA = posA + sizeA * 0.5f;
    const glm::vec2 minB = posB - sizeB * 0.5f;
    const glm::vec2 maxB = posB + sizeB * 0.5f;

    const glm::bvec2 overlap =
        bin::math::AABB(a->GetWorldPosition(), a->GetSize(), b->GetWorldPosition(), b->GetSize());

    Manifold m{};

    if(overlap.x and overlap.y)
    {
        m.penetration = glm::min(maxA - minB, maxB - minA);

        if(m.penetration.x < m.penetration.y)
            m.normal.x = (posA.x < posB.x) ? -1 : 1;  // Pointing from B to A
        else
            m.normal.y = (posA.y < posB.y) ? -1 : 1;  // Pointing from B to A

        return { true, m };
    }

    return { false, m };
}

const std::unordered_set<bin::BoxCollider*>& bin::Physics::GetColliders() const { return m_Colliders; }
