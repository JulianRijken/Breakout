#ifndef NODE_H
#define NODE_H

#include <Event.h>

#include <glm/mat3x3.hpp>
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

        virtual void Update() {}

        virtual void LateUpdate() {}

        virtual void FixedUpdate() {}

        template<typename Type>
        Type* GetFirstChildNodeOfType() const
        {
            for(auto* childPtr : m_ChildPtrs)
                if(auto castedChildPtr = dynamic_cast<Type*>(childPtr))
                    return castedChildPtr;

            return nullptr;
        }

        void Translate(const glm::vec2& delta);

        void SetLocalPosition(const glm::vec2& position);
        void SetLocalAngle(float angle);
        void SetLocalScale(const glm::vec2& scale);

        void SetWorldPosition(const glm::vec2& position);
        void SetWorldAngle(float angle);
        void SetWorldScale(const glm::vec2& scale);

        [[nodiscard]] const glm::vec2& GetLocalPosition() const;
        [[nodiscard]] float GetLocalAngle() const;
        [[nodiscard]] const glm::vec2& GetLocalScale() const;

        [[nodiscard]] const glm::mat3x3& GetWorldMatrix();
        [[nodiscard]] const glm::vec2& GetWorldPosition();
        [[nodiscard]] float GetWorldAngle();
        [[nodiscard]] const glm::vec2& GetWorldScale();

        void SetParent(Node* newParentPtr, bool worldPositionStays = true);
        void MarkForDestroy(bool destroy = true);

        [[nodiscard]] bool IsChild(Node* checkChildPtr) const;
        [[nodiscard]] bool IsMarkedForDestroy() const;
        [[nodiscard]] bool IsGettingDestroyed() const;

        bool m_UseAbsolutePosition{};  // / NOLINT - C.131: Avoid trivial getters and setters
        bool m_UseAbsoluteAngle{};     // / NOLINT - C.131: Avoid trivial getters and setters
        bool m_UseAbsoluteScale{};     // / NOLINT - C.131: Avoid trivial getters and setters

        bin::Event<Node&> m_OnDestroyedEvent{};


    private:
        void PropegateDirtyTransform();

        void UpdateWorldTransform();

        void PropagateGettingDestroyed();
        void ClearFromSceneGraph();

        glm::vec2 m_LocalPosition{ 0.0f, 0.0f };  // Primary Data
        float m_LocalAngle{ 0.0f };               // Primary Data
        glm::vec2 m_LocalScale{ 1.0f, 1.0f };     // Primary Data

        // Indicates if a re calculation of the derived data is needed
        bool m_TransformDirty{ true };

        glm::mat3x3 m_WorldTransformationMatrix{};  // Derived Data

        glm::vec2 m_WorldPosition{};  // Derived Data
        float m_WorldAngle{};         // Derived Data
        glm::vec2 m_WorldScale{};     // Derived Data


        bool m_MarkedForDestroy{ false };  // Marked by the user does not propagate
        bool m_GettingDestroyed{ false };  // Used by the SceneGraph

        Node* m_ParentPtr{ nullptr };
        std::unordered_set<Node*> m_ChildPtrs{};
    };
}  // namespace bin

#endif  // NODE_H
