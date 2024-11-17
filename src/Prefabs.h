#ifndef PREFABS_H
#define PREFABS_H

#include <glm/vec2.hpp>

namespace bin
{
    class Node;
}

namespace bout::prefabs
{
    bin::Node& BlueBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& GreenBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& YellowBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& OrangeBrick(const glm::vec2& size, bin::Node& parent);
    bin::Node& RedBrick(const glm::vec2& size, bin::Node& parent);

}  // namespace bout::prefabs
#endif  // PREFABS_H
