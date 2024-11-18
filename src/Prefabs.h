#ifndef PREFABS_H
#define PREFABS_H

#include <glm/vec2.hpp>
#include <string>

namespace bin
{
    class Node;
    class Button;
}  // namespace bin

namespace bout
{
    class Brick;

    namespace prefabs
    {
        bout::Brick& BlueBrick(const glm::vec2& size, bin::Node& parent);
        bout::Brick& GreenBrick(const glm::vec2& size, bin::Node& parent);
        bout::Brick& YellowBrick(const glm::vec2& size, bin::Node& parent);
        bout::Brick& OrangeBrick(const glm::vec2& size, bin::Node& parent);
        bout::Brick& RedBrick(const glm::vec2& size, bin::Node& parent);

        bin::Button& TextButton(const glm::vec2& size, const std::string& text, bin::Node& parent);
    }  // namespace prefabs
}  // namespace bout
#endif  // PREFABS_H
