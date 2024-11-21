#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <Node.h>

#include <unordered_set>

namespace bin
{
    class Sprite;
}

namespace bout
{
    class Brick;
    class Wall;

    class Playfield final : public bin::Node, public bin::IEventListener
    {

    public:
        Playfield(const glm::vec2& size);

        ~Playfield() override = default;
        Playfield(Playfield&&) = delete;
        Playfield(const Playfield&) = delete;
        Playfield& operator=(Playfield&&) = delete;
        Playfield& operator=(const Playfield&) = delete;

        [[nodiscard]] const glm::vec2& GetSize() const;

        bin::Event<> m_OnFieldCleared{};

        void BreakAllBricks();

        void ShowWalls();
        void HideWalls();

    private:
        void LateUpdate() override;

        void OnBrickDestroyedEvent(Node& brick);
        void OnPlayfieldCleared();

        void CorrectTopWallSize();

        static constexpr float WALL_WIDTH = 100.0f;

        bin::Sprite* m_LeftWallSpritePtr{};
        bin::Sprite* m_RightWallSpritePtr{};
        Wall* m_TopWallPtr{};
        Wall* m_RightWallPtr{};
        Wall* m_LeftWallPtr{};
        glm::vec2 m_Size{};
        std::unordered_set<Brick*> m_BrickPtrs{};
    };
}  // namespace bout


#endif  // PLAYFIELD_H
