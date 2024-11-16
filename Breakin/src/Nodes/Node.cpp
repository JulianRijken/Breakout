#include "Node.h"

void bin::Node::SetLocalPosition(const glm::vec2& position) { m_LocalPosition = position; }

void bin::Node::Translate(const glm::vec2& delta) { SetLocalPosition(m_LocalPosition + delta); }

const glm::vec2& bin::Node::GetWorldPosition() { return m_LocalPosition; }

const glm::vec2& bin::Node::GetLocalPosition() const { return m_LocalPosition; }
