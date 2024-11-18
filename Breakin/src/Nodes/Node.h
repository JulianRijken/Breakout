#ifndef NODE_H
#define NODE_H

#include <Event.h>

#include <glm/vec2.hpp>
#include <unordered_set>

namespace bin
{
    class Renderer;
    class Node
    {
        friend class SceneGraph;

    public:
        Node() = default;
        virtual ~Node();

        Node(Node&&) = delete;
        Node(const Node&) = delete;
        Node& operator=(Node&&) = delete;
        Node& operator=(const Node&) = delete;

        virtual void Draw(const bin::Renderer& /*unused*/) {}
        virtual void Update(){}
        virtual void FixedUpdate(){}

        void SetLocalPosition(const glm::vec2& position);
        void Translate(const glm::vec2& delta);
        void SetPositionDirty();

        void SetParent(Node* newParentPtr, bool worldPositionStays = true);
        void MarkForDestroy(bool destroy = true);

        [[nodiscard]] const glm::vec2& GetWorldPosition();
        [[nodiscard]] const glm::vec2& GetLocalPosition() const;
        [[nodiscard]] bool IsChild(Node* checkChildPtr) const;
        [[nodiscard]] bool IsMarkedForDestroy() const;

        bin::Event<Node&> m_OnDestroyedEvent{};

    private:
        void UpdateWorldPosition();
        void PropagateGettingDestroyed();
        void ClearFromSceneGraph();

        bool m_IsPositionDirty{ true };
        glm::vec2 m_LocalPosition{};  // Primary Data
        glm::vec2 m_WorldPosition{};  // Derived Data

        bool m_MarkedForDestroy{ false };  // Marked by the user does not propagate
        bool m_GettingDestroyed{ false };  // Used by the SceneGraph

        Node* m_ParentPtr{ nullptr };
        std::unordered_set<Node*> m_ChildPtrs{};
    };
}  // namespace bin

#endif  // NODE_H
