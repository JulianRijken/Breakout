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

    private:
        static constexpr float WALL_HIT_MOVE_DURATION{ 0.6f };
        static constexpr SDL_Color WALL_NORMAL_COLOR{ 70, 140, 70, 220 };
        static constexpr SDL_Color WALL_HIT_COLOR{ 100, 200, 100, 255 };

        void OnHit(const bin::Manifold& manifold);

        bin::Sprite* m_SpritePtr{};
        glm::vec2 m_MoveDirection{};
    };
}  // namespace bout
#endif  // WALL_H
