#include "Brick.h"

#include <BoxCollider.h>
#include <SceneGraph.h>

#include <iostream>

bout::Brick::Brick()
{
    auto* boxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 0.8f, 0.8f });
    boxColliderPtr->SetParent(this);
    boxColliderPtr->m_OnHit.AddListener(this, &bout::Brick::OnHit);
}

void bout::Brick::OnHit()
{
    std::cout << "On Hit" << std::endl;
    MarkForDestroy();
}
