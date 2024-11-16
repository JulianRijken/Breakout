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

void bin::SceneGraph::DrawAll() const
{
    for(const auto& node : m_Nodes)
        node->Draw();
}

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
