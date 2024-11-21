#include "Camera.h"

#include "Locator.h"
#include "Renderer.h"
#include "SceneGraph.h"

bin::Camera::Camera() { bin::SceneGraph::GetInstance().AddCamera(this); }

bin::Camera::~Camera() { bin::SceneGraph::GetInstance().RemoveCamera(this); }

float bin::Camera::GetOrthoSize() const { return m_OrthoSize; }

void bin::Camera::SetOrthoSize(float orthoSize) { m_OrthoSize = std::max(0.0f, orthoSize); }

glm::ivec2 bin::Camera::WorldToScreenScale(const glm::vec2& worldScale)
{
    const glm::vec2 worldSize = GetViewWorldSize();
    const glm::ivec2 windowSize = bin::Renderer::GetWindowSize();

    // Floats are not perfect, we use ceil as we prefer the pixel shown over cut off
    return { std::ceil(static_cast<float>(windowSize.x) / worldSize.x * worldScale.x),
             -std::ceil(static_cast<float>(windowSize.y) / worldSize.y * worldScale.y) };
}

glm::ivec2 bin::Camera::WorldToScreenPosition(const glm::vec2& worldPosition)
{
    const glm::ivec2 windowSize = bin::Renderer::GetWindowSize();
    const glm::vec4 clipSpacePos = GetViewProjectionMatrix() * glm::vec4(worldPosition, 0.0f, 1.0f);

    // We chose to round when it comes to positions
    return { std::round((clipSpacePos.x + 1.0f) * 0.5f * static_cast<float>(windowSize.x)),
             std::round((1.0f - clipSpacePos.y) * 0.5f * static_cast<float>(windowSize.y)) };
}

glm::vec2 bin::Camera::ScreenToWorldPosition(const glm::ivec2& screenPosition)
{
    const glm::ivec2 windowSize = bin::Renderer::GetWindowSize();

    glm::vec2 ndc;
    ndc.x = 2.0f * static_cast<float>(screenPosition.x) / static_cast<float>(windowSize.x) - 1.0f;
    ndc.y = 1.0f - 2.0f * static_cast<float>(screenPosition.y) / static_cast<float>(windowSize.y);

    const glm::vec4 worldPosition = glm::inverse(GetViewProjectionMatrix()) * glm::vec4(ndc, 0.0f, 1.0f);

    return { worldPosition.x, worldPosition.y };
}

glm::mat4 bin::Camera::GetViewProjectionMatrix()
{
    const float aspectRatio = bin::Renderer::GetAspectRatio();

    const glm::mat4 projection =
        glm::ortho(-m_OrthoSize * aspectRatio, m_OrthoSize * aspectRatio, -m_OrthoSize, m_OrthoSize, -1.0f, 1.0f);

    const glm::mat4 view = glm::translate(glm::mat4(1.0f), -glm::vec3(GetWorldPosition(), -10));

    return projection * view;
}

glm::vec2 bin::Camera::GetViewWorldSize()
{
    return { m_OrthoSize * 2.0f * bin::Renderer::GetAspectRatio(), m_OrthoSize * 2.0f };
}

