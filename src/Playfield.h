#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <Node.h>

#include <unordered_set>

namespace bout
{

    class Wall;
    class Brick;

    class Playfield final : public bin::Node, public bin::IEventListener
    {

    public:
        Playfield(const glm::vec2& size);

        [[nodiscard]] const glm::vec2& GetSize() const;

        bin::Event<> m_OnFieldCleared{};

    private:
        void OnBrickDestroyedEvent(Node& brick);
        void OnPlayfieldCleared();

        static constexpr float WALL_WIDTH = 50.0f;


        Wall* m_TopWall{};
        glm::vec2 m_Size{};
        std::unordered_set<Brick*> m_Bricks{};
    };
}  // namespace bout


#endif  // PLAYFIELD_H
