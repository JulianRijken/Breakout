#include "renderer.h"

#include <SDL_pixels.h>
#include <SDL_render.h>

#include <stdexcept>

#include "SceneGraph.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <SDL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

bin::Renderer::Renderer(SDL_Window* windowPtr) :
    m_RendererPtr(SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)),
    m_WindowPtr(windowPtr)
{
    if(m_RendererPtr == nullptr)
        throw std::runtime_error("Failed to create renderer");
}

void bin::Renderer::Render()
{
    SDL_SetRenderDrawColor(m_RendererPtr, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    SDL_RenderClear(m_RendererPtr);
    bin::SceneGraph::GetInstance().DrawAll();
    SDL_RenderPresent(m_RendererPtr);
}

void bin::Renderer::SetClearColor(const SDL_Color& color) { m_ClearColor = color; }

void bin::Renderer::DrawLine(const glm::vec2& from, const glm::vec2& to, const SDL_Color& color)
{
    const glm::ivec2 fromScreen = WorldToScreenPosition(from);
    const glm::ivec2 toScreen = WorldToScreenPosition(to);

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_RendererPtr, fromScreen.x, fromScreen.y, toScreen.x, toScreen.y);
}

void bin::Renderer::DrawBox(const glm::vec2& position, const glm::vec2& scale, const SDL_Color& color)
{
    const glm::ivec2 screenPos = WorldToScreenPosition(position);
    const glm::ivec2 screenScale = WorldToScreenScale(scale);

    const SDL_Rect rect = { screenPos.x, screenPos.y, screenScale.x, screenScale.y };

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_RendererPtr, &rect);
}

void bin::Renderer::DrawWireBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2&,
                                const SDL_Color& color)
{
    const glm::ivec2 screenPos = WorldToScreenPosition(position);
    const glm::ivec2 screenScale = WorldToScreenScale(scale);

    const SDL_Rect rect = { screenPos.x, screenPos.y, screenScale.x, screenScale.y };

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(m_RendererPtr, &rect);
}

glm::ivec2 bin::Renderer::GetWindowSize()
{
    // TODO: These values could be stored and only updated when the window changes
    //       Function encaptulation provided for this in the future

    int width{};
    int height{};
    SDL_GetWindowSize(m_WindowPtr, &width, &height);

    return { width, height };
}

float bin::Renderer::GetAspectRatio()
{
    // TODO: These values could be stored and only updated when the window changes
    //       Function encaptulation provided for this in the future

    auto windowSize = GetWindowSize();
    return static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
}

glm::ivec2 bin::Renderer::WorldToScreenScale(const glm::vec2& worldScale)
{
    const glm::vec2 worldSize = { m_OrthoSize * 2.0f * GetAspectRatio(), m_OrthoSize * 2.0f };
    const glm::ivec2 windowSize = GetWindowSize();

    // Floats are not perfect, we use ceil as we prefere the pixel shown over cut off
    return { std::ceil(static_cast<float>(windowSize.x) / worldSize.x * worldScale.x),
             -std::ceil(static_cast<float>(windowSize.y) / worldSize.y * worldScale.y) };
}

glm::ivec2 bin::Renderer::WorldToScreenPosition(const glm::vec2& worldPosition)
{
    const glm::ivec2 windowSize = GetWindowSize();
    const float aspectRatio = GetAspectRatio();

    const glm::mat4 projection =
        glm::ortho(-m_OrthoSize * aspectRatio, m_OrthoSize * aspectRatio, -m_OrthoSize, m_OrthoSize, -1.0f, 1.0f);

    const glm::vec4 clipSpacePos = projection * glm::vec4(worldPosition, 0, 1.0f);

    // We chose to round when it comes to positions
    return { std::round((clipSpacePos.x + 1.0f) * 0.5f * static_cast<float>(windowSize.x)),
             std::round((1.0f - clipSpacePos.y) * 0.5f * static_cast<float>(windowSize.y)) };
}

glm::vec2 bin::Renderer::ScreenToWorldPosition(const glm::ivec2& screenPosition)
{

    const glm::ivec2 windowSize = GetWindowSize();
    const float aspectRatio = GetAspectRatio();

    glm::vec2 ndc;
    ndc.x = 2.0f * static_cast<float>(screenPosition.x) / static_cast<float>(windowSize.x) - 1.0f;
    ndc.y = 1.0f - 2.0f * static_cast<float>(screenPosition.y) / static_cast<float>(windowSize.y);

    const glm::mat4 projection =
        glm::ortho(-m_OrthoSize * aspectRatio, m_OrthoSize * aspectRatio, -m_OrthoSize, m_OrthoSize, -1.0f, 1.0f);
    const glm::mat4 inverseProjection = glm::inverse(projection);

    const glm::vec4 worldPosition = inverseProjection * glm::vec4(ndc, 0.0f, 1.0f);

    return { worldPosition.x, worldPosition.y };
}
