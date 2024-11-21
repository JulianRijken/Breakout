#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <Node.h>

namespace bout
{
    class PauseMenu final : public bin::Node
    {
    public:
        PauseMenu();

        ~PauseMenu() override = default;
        PauseMenu(PauseMenu&&) = delete;
        PauseMenu(const PauseMenu&) = delete;
        PauseMenu& operator=(PauseMenu&&) = delete;
        PauseMenu& operator=(const PauseMenu&) = delete;

        void HideAndDestroy();

    private:
        static constexpr float ANIMATION_DURATION{ 0.2f };
    };
}  // namespace bout

#endif  // PAUSEMENU_H
