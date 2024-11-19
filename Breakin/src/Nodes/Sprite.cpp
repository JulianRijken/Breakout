#include "Sprite.h"

#include "Renderer.h"

void bin::Sprite::Draw(const Renderer& renderer)
{
    //
    renderer.DrawBox(GetWorldPosition(), { 1, 1 });
}
