#include "Prefabs.h"

#include <SceneGraph.h>

#include "Brick.h"

bin::Node& bout::prefabs::BlueBrick(const glm::vec2& size, bin::Node& parent)
{
    auto& brick = bin::SceneGraph::AddNode<Brick>(1, size, SDL_Color{ 45, 172, 214, 255 });
    brick.SetParent(&parent);
    return brick;
}

bin::Node& bout::prefabs::GreenBrick(const glm::vec2& size, bin::Node& parent)
{
    auto& brick = bin::SceneGraph::AddNode<Brick>(4, size, SDL_Color{ 65, 224, 70, 255 });
    brick.SetParent(&parent);
    return brick;
}

bin::Node& bout::prefabs::YellowBrick(const glm::vec2& size, bin::Node& parent)
{
    auto& brick = bin::SceneGraph::AddNode<Brick>(4, size, SDL_Color{ 235, 229, 59, 255 });
    brick.SetParent(&parent);
    return brick;
}

bin::Node& bout::prefabs::OrangeBrick(const glm::vec2& size, bin::Node& parent)
{
    auto& brick = bin::SceneGraph::AddNode<Brick>(7, size, SDL_Color{ 235, 165, 59, 255 });
    brick.SetParent(&parent);
    return brick;
}

bin::Node& bout::prefabs::RedBrick(const glm::vec2& size, bin::Node& parent)
{
    auto& brick = bin::SceneGraph::AddNode<Brick>(7, size, SDL_Color{ 235, 59, 59, 255 });
    brick.SetParent(&parent);
    return brick;
}
