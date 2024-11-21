#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <Node.h>

namespace bout
{
    class PauseMenu final : public bin::Node
    {
    public:
        PauseMenu();
        void HideAndDestroy();

    private:
        static constexpr float ANIMATION_DURATION{ 0.2f };
    };
}  // namespace bout

#endif  // PAUSEMENU_H
