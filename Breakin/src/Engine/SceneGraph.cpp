#include "SceneGraph.h"

#include <algorithm>
#include <iterator>

#include "GameTime.h"

void bin::SceneGraph::UpdateAll() const
{
    for(const auto& node : m_ActiveNodes)
        node->Update();
}

void bin::SceneGraph::LateUpdateAll() const
{
    for(const auto& node : m_ActiveNodes)
        node->LateUpdate();
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

    std::ranges::move(m_AddedNodes, std::back_inserter(m_ActiveNodes));
    m_AddedNodes.clear();
}

void bin::SceneGraph::CleanupNodesSetToDestroy()
{
    // 1.
    // Propagate all nodes marked for destroy
    // Nodes are first marked for destroy and then actually set getting destroyed
    //
    // Marked For Destroy -> Can be changed during the update and does not
    //                       tell the children. This is because you might un parent
    //                       as soon as you mark something for destroy.
    //
    // Getting Destroyed -> We go over all nodes again and go down the tree to set them
    //                      all to getting destroyed
    //
    // The OnDestroyed events is also called here
    for(const auto& node : m_ActiveNodes)
        if(node->IsMarkedForDestroy())
            node->PropagateGettingDestroyed();

    // 2. The nodes get removed from the graph
    //    This is after the destroy event so the event can still use the parent and children
    for(const auto& node : m_ActiveNodes)
        if(node->m_GettingDestroyed)
            node->ClearFromSceneGraph();

    // 3. Erase nodes from vector
    std::erase_if(m_ActiveNodes, [](const auto& node) { return node->m_GettingDestroyed; });
}

void bin::SceneGraph::LoadSceneSetToLoad()
{
    if(m_SceneToLoad < 0)
        return;

    ClearScene();

    const int loadingScene = m_SceneToLoad;

    // Reset scene to load
    m_SceneToLoad = -1;

    // Call functions to load scene
    m_SceneBinds[loadingScene]();

    // Ye someone actually loaded a scene while loading a scene
    if(m_SceneToLoad >= 0)
    {
        LoadSceneSetToLoad();
        return;
    }

    // Add nodes instantly
    MoveAddedNodesToActiveNodes();

    // TODO: We force reset the timescale
    //       this should be an option when calling load scene
    bin::GameTime::SetTimeScale(1.0f);
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
    if(m_BestCameraDirty)
    {
        const auto bestCameraIt = std::ranges::max_element(m_Cameras);

        if(bestCameraIt != m_Cameras.end())
            m_BestCamera = *bestCameraIt;
        else
            m_BestCamera = nullptr;

        m_BestCameraDirty = false;
    }

    return m_BestCamera;
}

void bin::SceneGraph::AddCamera(Camera* camera)
{
    m_BestCameraDirty = true;
    m_Cameras.insert(camera);
}

void bin::SceneGraph::RemoveCamera(Camera* camera)
{
    m_BestCameraDirty = true;
    m_Cameras.erase(camera);
}

