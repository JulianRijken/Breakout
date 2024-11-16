#include <Core.h>
#include <fmt/core.h>
#include <SceneGraph.h>

#include "Breakout.h"

void jul::Core::GameEntry()
{
    jul::SceneGraph::GetInstance().AddNode<Breakout>();
    //
}
