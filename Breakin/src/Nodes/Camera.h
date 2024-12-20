#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_pixels.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Node.h"

namespace bin
{
    class Camera final : public bin::Node
    {
    public:
        Camera();
        ~Camera() override;

        Camera(Camera&&) = delete;
        Camera(const Camera&) = delete;
        Camera& operator=(Camera&&) = delete;
        Camera& operator=(const Camera&) = delete;

        [[nodiscard]] float GetOrthoSize() const;

        void SetOrthoSize(float orthoSize);

        [[nodiscard]] glm::ivec2 WorldToScreenScale(const glm::vec2& worldScale) const;
        [[nodiscard]] glm::ivec2 WorldToScreenPosition(const glm::vec2& worldPosition) const;
        [[nodiscard]] glm::vec2 ScreenToWorldPosition(const glm::ivec2& screenPosition) const;

        [[nodiscard]] glm::mat4 GetViewProjectionMatrix() const;
        [[nodiscard]] glm::vec2 GetViewWorldSize() const;

        SDL_Color m_ClearColor{ 25, 25, 25, 0 };  // NOLINT - C.131: Avoid trivial getters and setters
        int m_Priority{ 0 };                      // NOLINT - C.131: Avoid trivial getters and setters

        // Allows for sorting the camera by priority
        bool operator<(const Camera& other) const { return m_Priority < other.m_Priority; }

    private:
        float m_OrthoSize{ 10 };
    };
}  // namespace bin

#endif  // CAMERA_H
