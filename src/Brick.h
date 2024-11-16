#ifndef BRICK_H
#define BRICK_H

#include <Event.h>
#include <Node.h>

namespace bout
{
    class Brick final : public bin::Node, public bin::IEventListener
    {
    public:
        Brick();

    private:
        void OnHit();
    };
}  // namespace bout

#endif  // BRICK_H
