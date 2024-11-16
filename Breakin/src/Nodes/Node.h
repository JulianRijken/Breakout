#ifndef NODE_H
#define NODE_H

#include <glm/vec2.hpp>
#include <unordered_set>

namespace bin
{
    class Node
    {
    public:
        virtual ~Node() = default;

        virtual void Draw(){};
        virtual void Update(){};
        virtual void FixedUpdate(){};

        void SetLocalPosition(const glm::vec2& position);
        void Translate(const glm::vec2& delta);

        void SetPositionDiry();

        [[nodiscard]] const glm::vec2& GetWorldPosition();
        [[nodiscard]] const glm::vec2& GetLocalPosition() const;
        [[nodiscard]] bool IsChild(Node* checkChildPtr) const;

        void SetParent(Node* newParentPtr, bool worldPositionStays = true);

    private:
        void UpdateWorldPosition();

        bool m_IsPositionDirty{ true };
        glm::vec2 m_LocalPosition{};  // Primary Data
        glm::vec2 m_WorldPosition{};  // Derived Data

        Node* m_ParentPtr{ nullptr };
        std::unordered_set<Node*> m_ChildPtrs{};
    };
}  // namespace bin

#endif  // NODE_H
