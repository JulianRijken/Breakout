#include "Sprite.h"

#include <iostream>

#include "Renderer.h"

void bin::Sprite::Draw(const Renderer& renderer)
{
    //
    std::cout << GetWorldAngle() << std::endl;
    renderer.DrawBox(GetWorldPosition(), GetWorldScale());
}
