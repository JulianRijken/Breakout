#ifndef TRAIL_H
#define TRAIL_H

#include <Node.h>
#include <SDL_pixels.h>

#include <deque>

namespace bout
{
    class Trail final : public bin::Node
    {
        using PastPoint = std::pair<glm::vec2, SDL_Color>;

    public:
        void SetTrailColor(SDL_Color newColor);

    private:
        void FixedUpdate() override;
        void Draw(const bin::Renderer& renderer) override;

        SDL_Color m_TrailColor{ 255, 255, 255, 255 };
        std::deque<PastPoint> m_PastPoints{};
    };
}  // namespace bin

#endif  // TRAIL_H
