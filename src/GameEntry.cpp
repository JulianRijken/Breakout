#include <Camera.h>
#include <Core.h>
#include <fmt/core.h>
#include <SceneGraph.h>

#include "Breakout.h"

void bin::Core::GameEntry()
{
    bin::SceneGraph::AddNode<bout::Breakout>();
}
