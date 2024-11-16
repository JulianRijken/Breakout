#include <fmt/core.h>

#include "Breakout.h"
#include "Core.h"
#include "SceneGraph.h"

void jul::Core::GameEntry()
{

    jul::SceneGraph::GetInstance().AddNode<Breakout>();
    //
}
