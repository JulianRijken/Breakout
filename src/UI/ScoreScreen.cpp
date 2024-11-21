#include "ScoreScreen.h"

#include <Camera.h>
#include <SceneGraph.h>

bin::ScoreScreen::ScoreScreen() { bin::SceneGraph::AddNode<bin::Camera>(); }
