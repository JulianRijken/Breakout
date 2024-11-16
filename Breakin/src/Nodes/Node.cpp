#include "Node.h"

#include <algorithm>

void bin::Node::SetLocalPosition(const glm::vec2& position)
{
    if(m_LocalPosition == position)
        return;

    m_LocalPosition = position;
    SetPositionDiry();
}

void bin::Node::Translate(const glm::vec2& delta) { SetLocalPosition(m_LocalPosition + delta); }

void bin::Node::SetPositionDiry()
{
    m_IsPositionDirty = true;

    for(Node* childPtr : m_ChildPtrs)
        if(not childPtr->m_IsPositionDirty)
            childPtr->SetPositionDiry();
}

const glm::vec2& bin::Node::GetWorldPosition()
{
    if(m_IsPositionDirty)
        UpdateWorldPosition();

    return m_WorldPosition;
}

const glm::vec2& bin::Node::GetLocalPosition() const { return m_LocalPosition; }

bool bin::Node::IsChild(Node* checkChildPtr) const
{
    if(m_ChildPtrs.contains(checkChildPtr))
        return true;

    // Recursivly checks all children
    return std::ranges::any_of(m_ChildPtrs,
                               [checkChildPtr](const Node* childPtr) { return childPtr->IsChild(checkChildPtr); });
}

void bin::Node::SetParent(Node* newParentPtr, bool worldPositionStays)
{
    // Avoid: same parent - new parent being this - new parent being a child of this
    if(newParentPtr == m_ParentPtr or newParentPtr == this or IsChild(newParentPtr))
        return;

    // Remove from old parent
    if(m_ParentPtr != nullptr)
    {
        m_ParentPtr->m_ChildPtrs.erase(this);

        if(worldPositionStays)
            m_LocalPosition += m_ParentPtr->GetWorldPosition();
    }

    m_ParentPtr = newParentPtr;

    // Add to new parent
    if(m_ParentPtr != nullptr)
    {
        m_ParentPtr->m_ChildPtrs.insert(this);

        if(worldPositionStays)
            m_LocalPosition -= m_ParentPtr->GetWorldPosition();
    }

    SetPositionDiry();
}

void bin::Node::UpdateWorldPosition()
{
    if(m_ParentPtr == nullptr)
        m_WorldPosition = m_LocalPosition;
    else
        m_WorldPosition = m_ParentPtr->GetWorldPosition() + m_LocalPosition;

    m_IsPositionDirty = false;
}
