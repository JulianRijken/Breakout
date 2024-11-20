#include "Renderer.h"

#include <SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

#include <iostream>
#include <stdexcept>

#include "Camera.h"
#include "SceneGraph.h"

bin::Renderer::Renderer(SDL_Window* windowPtr) :
    m_RendererPtr(SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)),
    m_WindowPtr(windowPtr)
{
    if(m_RendererPtr == nullptr)
        throw std::runtime_error("Failed to create renderer");

    SDL_SetRenderDrawBlendMode(m_RendererPtr, SDL_BLENDMODE_BLEND);

    m_EmptyTexture = std::make_unique<Texture>(
        SDL_CreateTexture(m_RendererPtr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1));
}

void bin::Renderer::Render() const
{
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    if(camera == nullptr)
    {
        std::cerr << "Scene has no camera" << '\n';
        return;
    }

    SDL_SetRenderDrawColor(
        m_RendererPtr, camera->m_ClearColor.r, camera->m_ClearColor.g, camera->m_ClearColor.b, camera->m_ClearColor.a);
    SDL_RenderClear(m_RendererPtr);

    // DrawUnitGrid();
    bin::SceneGraph::GetInstance().DrawAll(*this);

    SDL_RenderPresent(m_RendererPtr);
}

void bin::Renderer::DrawLine(const glm::vec2& from, const glm::vec2& to, const SDL_Color& color) const
{
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::ivec2 fromScreen = camera->WorldToScreenPosition(from);
    const glm::ivec2 toScreen = camera->WorldToScreenPosition(to);

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_RendererPtr, fromScreen.x, fromScreen.y, toScreen.x, toScreen.y);
}

void bin::Renderer::DrawTexture(const Texture* texture, const glm::vec2& position, const glm::vec2& scale,
                                float pixelsPerUnit, const glm::vec2& pivot) const
{
    assert(texture != nullptr && "Texture is null!");

    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::ivec2 textureSize = texture->GetSize();
    const glm::vec2 worldSize = static_cast<glm::vec2>(textureSize) / pixelsPerUnit * scale;

    const glm::vec2 offsetPosition = position - worldSize * pivot;
    const glm::ivec2 screenPos = camera->WorldToScreenPosition(offsetPosition);
    const glm::ivec2 screenScale = camera->WorldToScreenScale(worldSize);

    // We have to do  screenPos.y + screenScale.y because the rect has to go from top left
    const SDL_Rect destRect = { screenPos.x, screenPos.y + screenScale.y, screenScale.x, -screenScale.y };
    const SDL_Rect srcRect = { 0, 0, textureSize.x, textureSize.y };

    SDL_RenderCopy(m_RendererPtr, texture->GetSDLTexture(), &srcRect, &destRect);
}

void bin::Renderer::DrawRectRotated(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot,
                                    float angle, const SDL_Color& color) const
{
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::vec2 offsetPosition = position - scale * pivot;
    const glm::ivec2 screenPos = camera->WorldToScreenPosition(offsetPosition);
    const glm::ivec2 screenScale = camera->WorldToScreenScale(scale);

    auto* texture = m_EmptyTexture->GetSDLTexture();
    SDL_SetRenderTarget(m_RendererPtr, texture);
    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_RendererPtr);
    SDL_SetRenderTarget(m_RendererPtr, nullptr);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    const SDL_Rect destRect = { screenPos.x, screenPos.y + screenScale.y, screenScale.x, -screenScale.y };
    const SDL_Point pivotPoint = { static_cast<int>(std::round(pivot.x * static_cast<float>(destRect.w))),
                                   static_cast<int>(std::round(pivot.y * static_cast<float>(destRect.h))) };

    SDL_RenderCopyEx(m_RendererPtr, texture, nullptr, &destRect, -angle, &pivotPoint, SDL_FLIP_NONE);
}

void bin::Renderer::DrawRect(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot,
                             const SDL_Color& color) const
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

void bin::Renderer::DrawWireRect(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot,
                                 const SDL_Color& color) const
{
    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::vec2 offsetPosition = position - scale * pivot;
    const glm::ivec2 screenPos = camera->WorldToScreenPosition(offsetPosition);
    const glm::ivec2 screenScale = camera->WorldToScreenScale(scale);

    const SDL_Rect rect = { screenPos.x, screenPos.y, screenScale.x, screenScale.y };

    SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(m_RendererPtr, &rect);
}

glm::ivec2 bin::Renderer::GetWindowSize()
{
    // TODO: These values could be stored and only updated when the window changes
    //       Function encapsulation provided for this in the future

    int width{};
    int height{};
    SDL_GetWindowSize(Locator::Get<Renderer>().m_WindowPtr, &width, &height);

    return { width, height };
}

float bin::Renderer::GetAspectRatio()
{
    // TODO: These values could be stored and only updated when the window changes
    //       Function encapsulation provided for this in the future

    const glm::ivec2 windowSize = GetWindowSize();
    return static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
}

glm::ivec2 bin::Renderer::GetWindowSizeClamped()
{
    glm::vec2 windowSize = GetWindowSize();

    if(windowSize.y > windowSize.x)
        windowSize.y = windowSize.x;

    return windowSize;
}

float bin::Renderer::GetAspectRatioClamped()
{
    const glm::ivec2 windowSize = GetWindowSizeClamped();
    return static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
}

SDL_Texture* bin::Renderer::CreateTextureFromSurface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(Locator::Get<Renderer>().m_RendererPtr, surface);
}


void bin::Renderer::DrawUnitGrid() const
{
    Camera* camera = SceneGraph::GetInstance().GetBestCamera();
    assert(camera && "Camera is null, you are probably drawing outside of Draw()");

    const glm::vec2 worldSize = camera->GetViewWorldSize();
    const glm::vec2 worldCenter = camera->GetWorldPosition();

    const glm::ivec2 size = { std::ceil(worldSize.x * 0.5f + worldCenter.x),
                              std::ceil(worldSize.y * 0.5f + worldCenter.y) };


    auto getGridColor = [](int pos) -> SDL_Color
    {
        constexpr SDL_Color every100thLineColor{ 255, 255, 255, 100 };
        constexpr SDL_Color every10thLineColor{ 255, 255, 255, 40 };
        constexpr SDL_Color every1thLineColor{ 255, 255, 255, 15 };

        if(pos % 100 == 0)
            return every100thLineColor;

        if(pos % 10 == 0)
            return every10thLineColor;

        return every1thLineColor;
    };

    for(int x = -size.x; x < size.x; ++x)
        DrawLine({ x, size.y }, { x, -size.y }, getGridColor(x));

    for(int y = -size.y; y < size.y; ++y)
        DrawLine({ size.x, y }, { -size.x, y }, getGridColor(y));
}
