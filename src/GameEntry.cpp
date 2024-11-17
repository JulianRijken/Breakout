#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <Input.h>
#include <SceneGraph.h>

#include "Breakout.h"
#include "Resources.h"
#include "scenes.h"

void bin::Core::GameEntry()
{
    bin::Resources::LoadFont(0, "Fonts/NES_Font.ttf", 8);
    bin::Input::GetInstance().AddInputAction(bout::InputActionName::FireBall, { { SDL_SCANCODE_SPACE }, {} });
    bout::scenes::LoadScene(bout::scenes::Name::Game);
}
