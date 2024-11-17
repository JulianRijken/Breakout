#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <SceneGraph.h>

#include "Breakout.h"
#include "Resources.h"

void bin::Core::GameEntry()
{
    bin::Resources::LoadFont(0, "Fonts/NES_Font.ttf", 8);

    bin::SceneGraph::AddNode<bout::Breakout>();
}
