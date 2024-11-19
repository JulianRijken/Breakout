#ifndef SPRITE_H
#define SPRITE_H

#include "Node.h"

namespace bin
{
    class Sprite final : public Node
    {
    private:
        void Draw(const Renderer& renderer) override;
    };
}  // namespace bin

#endif  // SPRITE_H
