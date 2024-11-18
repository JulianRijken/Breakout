#ifndef PREFABS_H
#define PREFABS_H

#include <glm/vec2.hpp>
#include <string>

namespace bin
{
    class Node;
    class Button;
}  // namespace bin

namespace bout::prefabs
{
    bin::Node& BlueBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& GreenBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& YellowBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& OrangeBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& RedBrick(const glm::vec2& size, bin::Node& parent);

    bin::Button& TextButton(const glm::vec2& size, const std::string& text, bin::Node& parent);
}  // namespace bout::prefabs
#endif  // PREFABS_H
