#include "Physics.h"

void Physics::RegisterCollider(bin::BoxCollider* boxCollider) { m_Colliders.insert(boxCollider); }

void Physics::UnregisterColluder(bin::BoxCollider* boxCollider) { m_Colliders.erase(boxCollider); }
