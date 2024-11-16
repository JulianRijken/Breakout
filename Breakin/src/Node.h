#ifndef NODE_H
#define NODE_H

#include <glm/vec2.hpp>

namespace jul
{
    class Node
    {
    public:
        virtual ~Node() = default;

        virtual void Draw() const {};
        virtual void Update(){};
        virtual void FixedUpdate(){};

        const glm::vec2& GetLocalPosition();

    private:
        glm::vec2 m_LocalPosition{};

        // Node* m_Parent;
    };
}  // namespace jul

#endif  // NODE_H
