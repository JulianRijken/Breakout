#include "SceneGraph.h"

void jul::SceneGraph::Update()
{
    for(auto& node : m_Nodes)
        node->Update();
}

void jul::SceneGraph::FixedUpdate()
{
    for(auto& node : m_Nodes)
        node->FixedUpdate();
}

void jul::SceneGraph::Draw() const
{
    for(auto& node : m_Nodes)
        node->Draw();
}
