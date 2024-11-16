#include "Breakout.h"

#include <fmt/core.h>
#include <GameTime.h>
#include <Locator.h>
#include <MathExtensions.h>
#include <Paddle.h>
#include <Renderer.h>
#include <SceneGraph.h>
#include <SDL_mouse.h>

bout::Breakout::Breakout() { bin::SceneGraph::GetInstance().AddNode<Paddle>(); }

void bout::Breakout::Update()
{
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);


    auto& renderer = bin::Locator::Get<bin::Renderer>();
    const glm::vec2 mousePosition = { mouseX, mouseY };
    const glm::vec2 mousePositionWorld = renderer.ScreenToWorldPosition(mousePosition);


    m_paddleTargetPostion = std::clamp(mousePositionWorld.x, -10.0f, 10.0f);
    m_paddleTargetPostion = std::round(m_paddleTargetPostion);

    m_PaddlePosition = bin::math::LerpSmooth(
        m_PaddlePosition, m_paddleTargetPostion, PADDLE_MOVE_DURATION, bin::GameTime::GetDeltaTime());
}

void bout::Breakout::Draw() const
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();

    const double time = bin::GameTime::GetElapsedTime();
    constexpr double distance = 5;
    glm::vec2 pos = { std::cos(time), std::sin(time) };
    pos *= distance;

    renderer.DrawLine({ 0, 0 }, pos);

    // for(int x = 0; x < 5; ++x)
    // {
    //     for(int y = 0; y < 5; ++y)
    //     {
    //         // Testing
    //         const SDL_Color randomColor{ static_cast<Uint8>(bin::math::RandomRange(0, 255)),
    //                                      static_cast<Uint8>(bin::math::RandomRange(0, 255)),
    //                                      static_cast<Uint8>(bin::math::RandomRange(0, 255)),
    //                                      static_cast<Uint8>(bin::math::RandomRange(0, 255)) };

    //         renderer.DrawBox({ x * 2, y }, { 1, 1 }, randomColor);
    //     }
    // }

    renderer.DrawLine({ -5, 0 }, { 5, 0 }, { 217, 64, 237, 255 });
    renderer.DrawLine({ 0, -5 }, { 0, 5 }, { 217, 64, 237, 255 });
    renderer.DrawWireBox({ 0, 0 }, { 5, 5 });
    renderer.DrawWireBox({ 5, 5 }, { 5, 5 });


    renderer.DrawBox({ m_PaddlePosition, 0 }, { 1, 1 });
}
