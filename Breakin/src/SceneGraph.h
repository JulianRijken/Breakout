#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "Node.h"
#include "Singleton.h"

namespace bin
{
    class SceneGraph final : public Singleton<SceneGraph>
    {
    public:
        void UpdateAll();
        void FixedUpdateAll();
        void DrawAll() const;

        template<typename NodeType, typename... Args>
            requires std::derived_from<NodeType, Node>
        NodeType* AddNode(Args&&... args)
        {
            auto& addedComponent = m_Nodes.emplace_back(std::make_unique<NodeType>(std::forward<Args>(args)...));

            return static_cast<NodeType*>(addedComponent.get());
        }

    private:
        std::vector<std::unique_ptr<Node>> m_Nodes{};
    };

}  // namespace bin


#endif  // SCENE_H
