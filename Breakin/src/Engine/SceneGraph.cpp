#include "SceneGraph.h"

#include <algorithm>

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

void bin::SceneGraph::DrawAll()
{
    for(auto& node : m_Nodes)
        node->Draw();
}

void bin::SceneGraph::CleanupNodesSetToDestroy()
{
    // Propegate all nodes marked for destroy
    for(auto& node : m_Nodes)
        if(node->IsMarkedForDestroy())
            if(not node->m_GettingDestroyed)
                node->PropagateDestroy();

    for(auto iterator = m_Nodes.begin(); iterator != m_Nodes.end();)
        if((*iterator)->m_GettingDestroyed)
            iterator = m_Nodes.erase(iterator);
        else
            ++iterator;
}

void bin::SceneGraph::ClearAllNodes() { m_Nodes.clear(); }


bin::Camera* bin::SceneGraph::GetBestCamera()
{
    if(m_BestCameraDiry)
    {
        auto bestCameraIt = std::ranges::max_element(m_Cameras);

        if(bestCameraIt != m_Cameras.end())
            m_BestCamera = *bestCameraIt;
        else
            m_BestCamera = nullptr;

        m_BestCameraDiry = false;
    }

    return m_BestCamera;
}

void bin::SceneGraph::AddCamera(Camera* camera)
{
    m_BestCameraDiry = true;
    m_Cameras.insert(camera);
}

void bin::SceneGraph::RemoveCamera(Camera* camera)
{
    m_BestCameraDiry = true;
    m_Cameras.erase(camera);
}
