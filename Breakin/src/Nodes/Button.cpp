#include "Button.h"

#include <Input.h>
#include <SDL_mouse.h>

#include "GameTime.h"
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

    m_IsMouseOver = math::ABB(mouseWorldPosition, GetWorldPosition(), m_Size * GetWorldScale());
    m_IsMouseDown = (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));

    const float targetScale = m_IsMouseOver ? m_SelectedScale : 1.0f;
    m_CurrentScale = bin::math::LerpSmooth(m_CurrentScale, targetScale, m_ScaleLerpDuration, GameTime::GetDeltaTime());
    SetLocalScale(glm::vec2(1.0f) * m_CurrentScale);

    // TODO: Holding mouse down and hovering over also triggers now
    if(m_IsMouseDown)
    {
        if(not m_IsMouseOver)
        {
            m_IsPressed = false;
            return;
        }


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
    m_Color = m_IdleColor;

    if(m_IsMouseOver)
        m_Color = m_SelectedColor;

    if(m_IsPressed)
        m_Color = m_PressedColor;

    renderer.DrawRect(GetWorldPosition(), m_Size * GetWorldScale(), { 0.5f, 0.5f }, m_Color);
}

void bin::Button::OnPress() { m_OnPress.Invoke(); }

void bin::Button::OnReleased() { m_OnReleased.Invoke(); }
