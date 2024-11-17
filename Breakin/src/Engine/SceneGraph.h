#ifndef SCENE_H
#define SCENE_H

#include <memory>
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
    public:
        void UpdateAll() const;
        void FixedUpdateAll() const;
        void DrawAll(const bin::Renderer& renderer) const;

        void MoveAddedNodesToActiveNodes();
        void CleanupNodesSetToDestroy();
        void Clear();

        template<typename NodeType, typename... Args>
            requires std::derived_from<NodeType, Node>
        static NodeType& AddNode(Args&&... args)
        {
            auto& addedNodes =
                GetInstance().m_AddedNodes.emplace_back(std::make_unique<NodeType>(std::forward<Args>(args)...));

            return *static_cast<NodeType*>(addedNodes.get());
        }

        // Reruns camera with the highest priority
        // Can be nullptr
        [[nodiscard]] Camera* GetBestCamera();

        void AddCamera(Camera* camera);
        void RemoveCamera(Camera* camera);

    private:
        bool m_BestCameraDiry{ false };
        Camera* m_BestCamera{ nullptr };

        // There is a seperation because
        // added nodes can only update the next frame
        std::vector<std::unique_ptr<Node>> m_AddedNodes{};   // Nodes that set to spawn
        std::vector<std::unique_ptr<Node>> m_ActiveNodes{};  // Nodes that are active in the scene
        std::unordered_set<Camera*> m_Cameras{};
    };

}  // namespace bin
#endif  // SCENE_H
