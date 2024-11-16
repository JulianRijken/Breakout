#include "BoxCollider.h"

#include "Physics.h"
#include "Renderer.h"

bin::BoxCollider::BoxCollider(const glm::vec2& size) :
    m_Size(size)
{
    Locator::Get<Physics>().RegisterCollider(this);
}

bin::BoxCollider::~BoxCollider() { Locator::Get<Physics>().UnregisterCollider(this); }

const glm::vec2& bin::BoxCollider::GetSize() { return m_Size; }

void bin::BoxCollider::Draw()
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox(GetWorldPosition(), m_Size, { 0.5f, 0.5f }, { 89, 247, 115, 125 });
}
