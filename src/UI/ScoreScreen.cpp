#include "ScoreScreen.h"

#include <Camera.h>
#include <SceneGraph.h>

bout::ScoreScreen::ScoreScreen() { bin::SceneGraph::AddNode<bin::Camera>(); }
