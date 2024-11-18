#include "Prefabs.h"

#include <Button.h>
#include <Font.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <Texture.h>

#include "Brick.h"
#include "GlobalSettings.h"


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

bin::Button& bout::prefabs::TextButton(const glm::vec2& size, const std::string& text, bin::Node& parent)
{
    auto& startButton = bin::SceneGraph::AddNode<bin::Button>(size);
    startButton.SetParent(&parent);

    auto& startText = bin::SceneGraph::AddNode<bin::Text>(text,
                                                          bin::Resources::GetFont(FontName::NES_Font),
                                                          glm::vec2{ 0.5f, 0.5f },
                                                          size.y * 0.8f,
                                                          SDL_Color{ 0, 0, 0, 200 });
    startText.SetParent(&startButton, false);

    return startButton;
}
