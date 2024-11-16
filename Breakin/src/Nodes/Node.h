#ifndef NODE_H
#define NODE_H

#include <glm/vec2.hpp>

namespace bin
{
    class Node
    {
    public:
        virtual ~Node() = default;

        virtual void Draw() const {};
        virtual void Update(){};
        virtual void FixedUpdate(){};

        void SetLocalPosition(const glm::vec2& position);
        void Translate(const glm::vec2& delta);

        [[nodiscard]] const glm::vec2& GetWorldPosition();
        [[nodiscard]] const glm::vec2& GetLocalPosition() const;

    private:
        glm::vec2 m_LocalPosition{};

        // Node* m_Parent;
    };
}  // namespace bin

#endif  // NODE_H
