#include "BoxCollider.h"

#include "Physics.h"

bin::BoxCollider::BoxCollider(const glm::vec2& size, uint16_t layers) :
    m_Layers(layers),
    m_Size(size)
{
    Locator::Get<Physics>().RegisterCollider(this);
}

bin::BoxCollider::~BoxCollider() { Locator::Get<Physics>().UnregisterCollider(this); }

glm::vec2 bin::BoxCollider::GetSize() const { return m_Size * GetWorldScale(); }

bool bin::BoxCollider::CompareLayers(uint16_t layers) const { return layers & m_Layers; }
