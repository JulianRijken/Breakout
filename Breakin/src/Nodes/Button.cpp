#include "Button.h"

#include <Input.h>
#include <SDL_mouse.h>

#include "MathExtensions.h"
#include "Renderer.h"
#include "SceneGraph.h"

bin::Button::Button(const glm::vec2& size) :
    m_Size(size)
{
}

void bin::Button::Update()
{
    const glm::ivec2 mousePosition = Input::GetMousePosition();
    const Uint32 mouseState = Input::GetMouseState();

    const Camera* camera = SceneGraph::GetInstance().GetBestCamera();

    if(camera == nullptr)
        return;

    const glm::vec2 mouseWorldPosition = camera->ScreenToWorldPosition(mousePosition);

    m_IsSelected = math::ABB(mouseWorldPosition, GetWorldPosition(), m_Size);
    m_IsDown = (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));

    if(m_IsDown)
    {
        if(not m_IsSelected)
            return;

        if(m_IsPressed)
            return;

        OnPress();

        m_IsPressed = true;
    }
    else
    {
        if(not m_IsPressed)
            return;

        OnReleased();
        m_IsPressed = false;
    }
}

void bin::Button::Draw(const Renderer& renderer)
{
    m_Color = { 200, 200, 200, 255 };

    if(m_IsSelected)
        m_Color = { 255, 255, 255, 255 };

    if(m_IsPressed)
        m_Color = { 255, 150, 150, 255 };

    renderer.DrawBox(GetWorldPosition(), m_Size, { 0.5f, 0.5f }, m_Color);
}

void bin::Button::OnPress() { m_OnPress.Invoke(); }

void bin::Button::OnReleased() { m_OnReleased.Invoke(); }
