#include "SceneGraph.h"

void bin::SceneGraph::UpdateAll()
{
    for(auto& node : m_Nodes)
        node->Update();
}

void bin::SceneGraph::FixedUpdateAll()
{
    for(auto& node : m_Nodes)
        node->FixedUpdate();
}

void bin::SceneGraph::DrawAll() const
{
    for(auto& node : m_Nodes)
        node->Draw();
}
