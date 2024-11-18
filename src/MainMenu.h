#ifndef MAINMENU_H
#define MAINMENU_H

#include <Event.h>

#include "Node.h"


namespace bin
{
    class Text;
}

namespace bout
{
    class MainMenu final : public bin::Node, public bin::IEventListener
    {
    public:
        MainMenu();

    private:
        void OnStartButtonPress();
        void OnQuitButtonPress();
    };
}  // namespace bout


#endif  // MAINMENU_H
