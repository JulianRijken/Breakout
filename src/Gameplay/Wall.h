#ifndef WALL_H
#define WALL_H
#include <Node.h>
#include <SDL_pixels.h>

namespace bin
{
    class Sprite;
    struct Manifold;
}  // namespace bin

namespace bout
{
    class Wall final : public bin::Node, public bin::IEventListener
    {
    public:
        Wall(const glm::vec2& moveDirection);

        ~Wall() override = default;
        Wall(Wall&&) = delete;
        Wall(const Wall&) = delete;
        Wall& operator=(Wall&&) = delete;
        Wall& operator=(const Wall&) = delete;

    private:
        static constexpr float WALL_HIT_MOVE_DURATION{ 0.6f };
        static constexpr SDL_Color WALL_NORMAL_COLOR{ 80, 80, 100, 220 };
        static constexpr SDL_Color WALL_HIT_COLOR{ 100, 100, 200, 245 };

        void OnHit(const bin::Manifold& manifold);

        void BounceWall();

        bin::Sprite* m_SpritePtr{};
        glm::vec2 m_MoveDirection{};
    };
}  // namespace bout
#endif  // WALL_H
