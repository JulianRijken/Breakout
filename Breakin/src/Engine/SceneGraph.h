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
    class SceneGraph final : public Singleton<SceneGraph>
    {
    public:
        void UpdateAll() const;
        void FixedUpdateAll() const;
        void DrawAll() const;

        void CleanupNodesSetToDestroy();
        void ClearAllNodes();

        template<typename NodeType, typename... Args>
            requires std::derived_from<NodeType, Node>
        static NodeType* AddNode(Args&&... args)
        {
            auto& addedNode =
                GetInstance().m_Nodes.emplace_back(std::make_unique<NodeType>(std::forward<Args>(args)...));

            return static_cast<NodeType*>(addedNode.get());
        }

        // Reruns camera with the highest priority
        // Can be nullptr
        [[nodiscard]] Camera* GetBestCamera();

        void AddCamera(Camera* camera);
        void RemoveCamera(Camera* camera);

    private:
        bool m_BestCameraDiry{ false };
        Camera* m_BestCamera{ nullptr };

        std::vector<std::unique_ptr<Node>> m_Nodes{};
        std::unordered_set<Camera*> m_Cameras{};
    };

}  // namespace bin


#endif  // SCENE_H
