#ifndef TRAIL_H
#define TRAIL_H

#include <Node.h>
#include <SDL_pixels.h>

#include <deque>

namespace bin
{
    class Trail final : public bin::Node
    {
        using PastPoint = std::pair<glm::vec2, SDL_Color>;

    public:
        Trail() = default;
        ~Trail() override = default;
        Trail(Trail&&) = delete;
        Trail(const Trail&) = delete;
        Trail& operator=(Trail&&) = delete;
        Trail& operator=(const Trail&) = delete;

        void SetTrailColor(const SDL_Color& newColor);

    private:
        void FixedUpdate() override;
        void Draw(const bin::Renderer& renderer) override;

        void IncrementPastPoints();

        SDL_Color m_TrailColor{ 255, 255, 255, 255 };

        // NOTE: would ideally use a ring buffer as we know the size
        std::deque<PastPoint> m_PastPoints{};
    };
}  // namespace bin

#endif  // TRAIL_H
