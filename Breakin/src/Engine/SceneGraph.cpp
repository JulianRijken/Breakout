#include "SceneGraph.h"

#include <algorithm>
#include <iterator>


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
    // 1.
    // Propagate all nodes marked for destroy
    // Nodes are first marked for destroy and then actually set getting destroyed
    //
    // Marked For Destroy -> Can be changed during the update and does not
    //                       tell the children. This is becuase you might un parent
    //                       as soon as you mark something for desroy.
    //
    // Getting Destroyed -> We go over all nodes again and go down the tree to set them
    //                      all to getting destroyed
    //
    // The OnDestroyed events is also called here
    for(const auto& node : m_ActiveNodes)
        if(node->IsMarkedForDestroy())
            node->PropagateGettingDestroyed();

    // 2. The nodes get removed from the graph
    //    This is after the destroy event so the event can still use the parent and childs
    for(const auto& node : m_ActiveNodes)
        if(node->m_GettingDestroyed)
            node->ClearFromSceneGraph();

    // 3. Erase nodes from vector
    std::erase_if(m_ActiveNodes, [](const auto& node) { return node->m_GettingDestroyed; });
}

void bin::SceneGraph::ActivateSceneSetToLoad()
{
    if(m_SceneToLoad < 0)
        return;

    ClearScene();

    // Call functions to load scene
    m_SceneBinds[m_SceneToLoad]();

    // Add nodes instantly
    MoveAddedNodesToActiveNodes();

    // Reset scene to load
    m_SceneToLoad = -1;
}

void bin::SceneGraph::ClearScene()
{
    do
    {
        MoveAddedNodesToActiveNodes();

        for(const auto& node : m_ActiveNodes)
            node->PropagateGettingDestroyed();

        m_ActiveNodes.clear();

        // Keep checking as Destroyed event might add nodes to the scene
    } while(not m_AddedNodes.empty());
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

