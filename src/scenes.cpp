#include "Scenes.h"

#include <Breakout.h>
#include <SceneGraph.h>


void bout::scenes::LoadScene(bout::scenes::Name name)
{
    bin::SceneGraph::GetInstance().Clear();

    switch(name)
    {
        case Name::Game:

            bin::SceneGraph::AddNode<bout::Breakout>();

            break;
        case Name::MainMenu:
            throw std::runtime_error("Main Menu Not Implemented");
            break;
    }
}
