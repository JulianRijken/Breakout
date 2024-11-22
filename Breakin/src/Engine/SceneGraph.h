#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Camera.h"
#include "Node.h"
#include "Singleton.h"

namespace bin
{
    class Renderer;

    class SceneGraph final : public Singleton<SceneGraph>
    {
        friend class Core;
        friend class Camera;
        friend class Renderer;

    public:
        template<typename NodeType, typename... Args>
            requires std::derived_from<NodeType, Node>
        static NodeType& AddNode(Args&&... args)
        {
            auto& addedNodes =
                GetInstance().m_AddedNodes.emplace_back(std::make_unique<NodeType>(std::forward<Args>(args)...));

            return *static_cast<NodeType*>(addedNodes.get());
        }

        template<typename SceneName>
        static void BindScene(SceneName sceneName, std::function<void()>&& function)
        {
            const int sceneId = static_cast<int>(sceneName);
            assert(not GetInstance().m_SceneBinds.contains(sceneId) && "Scene Alread Bound");

            GetInstance().m_SceneBinds[sceneId] = std::move(function);
        }

        template<typename SceneName>
        static void LoadScene(SceneName sceneName)
        {
            const int sceneId = static_cast<int>(sceneName);
            assert(GetInstance().m_SceneBinds.contains(sceneId) && "Scene Not Bound");

            GetInstance().m_SceneToLoad = sceneId;
        }

        template<typename NodeType>
            requires std::derived_from<NodeType, Node>
        static std::vector<NodeType*> GetAllNodesOfClass()
        {
            std::vector<NodeType*> nodesOfClass;

            for(const auto& node : GetInstance().m_ActiveNodes)
                if(auto* castedNode = dynamic_cast<NodeType*>(node.get()))
                    nodesOfClass.push_back(castedNode);

            return nodesOfClass;
        }

        // Reruns camera with the highest priority
        // Can be nullptr
        [[nodiscard]] Camera* GetBestCamera() const;

    private:
        void AddCamera(Camera* camera);
        void RemoveCamera(Camera* camera);
        void UpdateAll() const;
        void LateUpdateAll() const;
        void FixedUpdateAll() const;
        void DrawAll(const bin::Renderer& renderer) const;

        void MoveAddedNodesToActiveNodes();
        void CleanupNodesSetToDestroy();
        void LoadSceneSetToLoad();
        void ClearScene();


        mutable bool m_BestCameraDirty{ false };
        mutable Camera* m_BestCamera{ nullptr };

        // There is a separation because
        // added nodes can only update the next frame
        std::vector<std::unique_ptr<Node>> m_AddedNodes{};   // Nodes that set to spawn
        std::vector<std::unique_ptr<Node>> m_ActiveNodes{};  // Nodes that are active in the scene
        std::unordered_set<Camera*> m_Cameras{};

        // Scene loading is handled here as it allow for loading at the end of the frame
        int m_SceneToLoad{ -1 };  // -1 Indicating no scene to load
        std::unordered_map<int, std::function<void()>> m_SceneBinds{};
    };

}  // namespace bin
#endif  // SCENE_H
