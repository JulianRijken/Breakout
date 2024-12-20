#include "Node.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

bin::Node::~Node() { assert(m_GettingDestroyed && "Node destructor called before destory"); }

void bin::Node::Translate(const glm::vec2& delta) { SetLocalPosition(m_LocalPosition + delta); }

void bin::Node::SetLocalPosition(const glm::vec2& position)
{
    if(m_LocalPosition == position)
        return;

    m_LocalPosition = position;
    PropagateDirtyTransform();
}

void bin::Node::SetLocalAngle(float angle)
{
    if(m_LocalAngle == angle)
        return;

    m_LocalAngle = angle;
    PropagateDirtyTransform();
}

void bin::Node::SetLocalScale(const glm::vec2& scale)
{
    if(m_LocalScale == scale)
        return;

    m_LocalScale = scale;
    PropagateDirtyTransform();
}

void bin::Node::SetWorldPosition(const glm::vec2& position)
{
    if(m_ParentPtr == nullptr)
        SetLocalPosition(position);
    else
        SetLocalPosition(glm::vec2(glm::inverse(m_ParentPtr->GetWorldMatrix()) * glm::vec3(position, 1.0f)));
}

void bin::Node::SetWorldAngle(float angle)
{
    if(m_ParentPtr == nullptr)
        SetLocalAngle(angle);
    else
        SetLocalAngle(angle - m_ParentPtr->GetWorldAngle());
}

void bin::Node::SetWorldScale(const glm::vec2& scale)
{
    if(m_ParentPtr == nullptr)
        SetLocalScale(scale);
    else
        SetLocalScale(scale / m_ParentPtr->GetWorldScale());
}

const glm::vec2& bin::Node::GetLocalPosition() const { return m_LocalPosition; }

float bin::Node::GetLocalAngle() const { return m_LocalAngle; }

const glm::vec2& bin::Node::GetLocalScale() const { return m_LocalScale; }

const glm::mat3x3& bin::Node::GetWorldMatrix() const
{
    if(m_TransformDirty)
        UpdateWorldTransform();

    return m_WorldTransformationMatrix;
}

const glm::vec2& bin::Node::GetWorldPosition() const
{
    if(m_TransformDirty)
        UpdateWorldTransform();

    return m_WorldPosition;
}

float bin::Node::GetWorldAngle() const
{
    if(m_TransformDirty)
        UpdateWorldTransform();

    return m_WorldAngle;
}

const glm::vec2& bin::Node::GetWorldScale() const
{
    if(m_TransformDirty)
        UpdateWorldTransform();

    return m_WorldScale;
}

bool bin::Node::IsChild(Node* checkChildPtr) const
{
    if(m_ChildPtrs.contains(checkChildPtr))
        return true;

    // Recursively checks all children
    return std::ranges::any_of(m_ChildPtrs,
                               [checkChildPtr](const Node* childPtr) { return childPtr->IsChild(checkChildPtr); });
}

bool bin::Node::IsMarkedForDestroy() const { return m_MarkedForDestroy; }

bool bin::Node::IsGettingDestroyed() const { return m_GettingDestroyed; }

void bin::Node::PropagateDirtyTransform() const
{
    m_TransformDirty = true;

    for(Node* childPtr : m_ChildPtrs)
        if(not childPtr->m_TransformDirty)
            childPtr->PropagateDirtyTransform();
}

void bin::Node::UpdateWorldTransform() const
{
    if(m_ParentPtr == nullptr)
    {
        m_WorldPosition = m_LocalPosition;
        m_WorldAngle = m_LocalAngle;
        m_WorldScale = m_LocalScale;
    }
    else
    {
        m_WorldPosition = m_UseAbsolutePosition
                            ? m_LocalPosition
                            : glm::vec2(m_ParentPtr->GetWorldMatrix() * glm::vec3(m_LocalPosition, 1.0f));
        m_WorldAngle = m_UseAbsoluteAngle ? m_LocalAngle : m_ParentPtr->GetWorldAngle() + m_LocalAngle;
        m_WorldScale = m_UseAbsoluteScale ? m_LocalScale : m_ParentPtr->GetWorldScale() * m_LocalScale;
    }

    m_WorldTransformationMatrix = glm::mat3x3(1.0f);
    m_WorldTransformationMatrix = glm::translate(m_WorldTransformationMatrix, m_WorldPosition);
    m_WorldTransformationMatrix = glm::rotate(m_WorldTransformationMatrix, glm::radians(m_WorldAngle));
    m_WorldTransformationMatrix = glm::scale(m_WorldTransformationMatrix, m_WorldScale);

    m_TransformDirty = false;
}

void bin::Node::SetParent(Node* newParentPtr, bool worldTransformStays)
{
    if(newParentPtr == m_ParentPtr or newParentPtr == this or IsChild(newParentPtr))
        return;

    // Remove from old parent
    if(m_ParentPtr != nullptr)
    {
        m_ParentPtr->m_ChildPtrs.erase(this);

        if(worldTransformStays)
        {
            m_LocalPosition += m_ParentPtr->GetWorldPosition();
            m_LocalAngle += m_ParentPtr->GetWorldAngle();
            m_LocalScale *= m_ParentPtr->GetWorldScale();
        }
    }

    m_ParentPtr = newParentPtr;

    // Add to new parent
    if(m_ParentPtr != nullptr)
    {
        m_ParentPtr->m_ChildPtrs.insert(this);

        if(worldTransformStays)
        {
            m_LocalPosition -= m_ParentPtr->GetWorldPosition();
            m_LocalAngle -= m_ParentPtr->GetWorldAngle();
            m_LocalScale /= m_ParentPtr->GetWorldScale();
        }
    }

    PropagateDirtyTransform();
}

void bin::Node::MarkForDestroy(bool destroy) { m_MarkedForDestroy = destroy; }

void bin::Node::PropagateGettingDestroyed()
{
    if(m_GettingDestroyed)
        return;

    m_GettingDestroyed = true;
    m_OnDestroyedEvent.Invoke(*this);

    for(Node* child : m_ChildPtrs)
        child->PropagateGettingDestroyed();
}

void bin::Node::ClearFromSceneGraph()
{
    if(m_ParentPtr != nullptr)
        m_ParentPtr->m_ChildPtrs.erase(this);

    m_ChildPtrs.clear();
}
