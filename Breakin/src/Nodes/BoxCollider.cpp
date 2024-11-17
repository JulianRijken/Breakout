#include "BoxCollider.h"

#include "Physics.h"
#include "Renderer.h"

bin::BoxCollider::BoxCollider(const glm::vec2& size, uint16_t layers) :
    m_Layers(layers),
    m_Size(size)
{
    Locator::Get<Physics>().RegisterCollider(this);
}

bin::BoxCollider::~BoxCollider() { Locator::Get<Physics>().UnregisterCollider(this); }

const glm::vec2& bin::BoxCollider::GetSize() const { return m_Size; }

bool bin::BoxCollider::CompareLayers(uint16_t layers) const { return layers & m_Layers; }

void bin::BoxCollider::Draw(const Renderer& renderer)
{
    renderer.DrawBox(GetWorldPosition(), m_Size, { 0.5f, 0.5f }, { 89, 247, 115, 125 });
}
