#include "SceneGraph.h"

#include <algorithm>

void bin::SceneGraph::UpdateAll() const
{
    for(const auto& node : m_ActiveNodes)
        node->Update();
}

void bin::SceneGraph::FixedUpdateAll() const
{
    for(const auto& node : m_ActiveNodes)
        node->FixedUpdate();
}

void bin::SceneGraph::DrawAll(const bin::Renderer& renderer) const
{
    for(const auto& node : m_ActiveNodes)
        node->Draw(renderer);
}

void bin::SceneGraph::MoveAddedNodesToActiveNodes()
{
    if(m_AddedNodes.empty())
        return;

    std::move(m_AddedNodes.begin(), m_AddedNodes.end(), std::back_inserter(m_ActiveNodes));
    m_AddedNodes.clear();
}

void bin::SceneGraph::CleanupNodesSetToDestroy()
{
    // Propagate all nodes marked for destroy
    for(const auto& node : m_ActiveNodes)
        if(node->IsMarkedForDestroy())
            if(not node->m_GettingDestroyed)
                node->PropagateDestroy();

    for(const auto& node : m_ActiveNodes)
        if(node->m_GettingDestroyed)
            node->ClearFromSceneGraph();

    for(auto iterator = m_ActiveNodes.begin(); iterator != m_ActiveNodes.end();)
        if((*iterator)->m_GettingDestroyed)
            iterator = m_ActiveNodes.erase(iterator);
        else
            ++iterator;
}

void bin::SceneGraph::LoadScenesSetToLoad()
{
    if(m_SceneToLoad < 0)
        return;

    ClearScene();

    // Call functions to load scene
    m_SceneBinds[m_SceneToLoad]();
    m_SceneToLoad = -1;
}

void bin::SceneGraph::ClearScene()
{
    MoveAddedNodesToActiveNodes();
    m_ActiveNodes.clear();
}


bin::Camera* bin::SceneGraph::GetBestCamera()
{
    if(m_BestCameraDiry)
    {
        const auto bestCameraIt = std::ranges::max_element(m_Cameras);

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

