#include "renderer.h"

#include <SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

#include <stdexcept>

#include "Camera.h"
#include "SceneGraph.h"


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
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::ivec2 fromScreen = camera->WorldToScreenPosition(from);
    const glm::ivec2 toScreen = camera->WorldToScreenPosition(to);

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_RendererPtr, fromScreen.x, fromScreen.y, toScreen.x, toScreen.y);
}

void bin::Renderer::DrawBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot,
                            const SDL_Color& color)
{
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::vec2 offsetPosition = position - scale * pivot;

    const glm::ivec2 screenPos = camera->WorldToScreenPosition(offsetPosition);
    const glm::ivec2 screenScale = camera->WorldToScreenScale(scale);

    const SDL_Rect rect = { screenPos.x, screenPos.y, screenScale.x, screenScale.y };

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_RendererPtr, &rect);
}

void bin::Renderer::DrawWireBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2&,
                                const SDL_Color& color)
{
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::ivec2 screenPos = camera->WorldToScreenPosition(position);
    const glm::ivec2 screenScale = camera->WorldToScreenScale(scale);

    const SDL_Rect rect = { screenPos.x, screenPos.y, screenScale.x, screenScale.y };

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(m_RendererPtr, &rect);
}

glm::ivec2 bin::Renderer::GetWindowSize() const
{
    // TODO: These values could be stored and only updated when the window changes
    //       Function encaptulation provided for this in the future

    int width{};
    int height{};
    SDL_GetWindowSize(m_WindowPtr, &width, &height);

    return { width, height };
}

float bin::Renderer::GetAspectRatio() const
{
    // TODO: These values could be stored and only updated when the window changes
    //       Function encaptulation provided for this in the future

    auto windowSize = GetWindowSize();
    return static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
}
