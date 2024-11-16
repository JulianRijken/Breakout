#include "Brick.h"

#include <BoxCollider.h>
#include <SceneGraph.h>

#include "Breakout.h"


bout::Brick::Brick()
{
    auto* boxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.8f, 0.8f }, bout::layer::BRICK);
    boxColliderPtr->SetParent(this);
    boxColliderPtr->m_OnHit.AddListener(this, &bout::Brick::OnHit);
}

void bout::Brick::OnHit()
{
    MarkForDestroy();
}
