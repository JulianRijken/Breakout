#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <SceneGraph.h>

#include "Resources.h"
#include "scenes.h"


void bin::Core::GameEntry()
{
    bin::Resources::LoadFont(0, "Fonts/NES_Font.ttf", 8);
    bout::scenes::LoadScene(bout::scenes::Name::Game);
}
