#include "Brick.h"

#include <BoxCollider.h>
#include <SceneGraph.h>

bout::Brick::Brick()
{
    auto* boxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.8f, 0.8f });
    boxColliderPtr->SetParent(this);
}
