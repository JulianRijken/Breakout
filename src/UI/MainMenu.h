#ifndef MAINMENU_H
#define MAINMENU_H

#include <Event.h>

#include "GlobalSettings.h"
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

        ~MainMenu() override = default;
        MainMenu(MainMenu&&) = delete;
        MainMenu(const MainMenu&) = delete;
        MainMenu& operator=(MainMenu&&) = delete;
        MainMenu& operator=(const MainMenu&) = delete;

    private:
        bool m_StartingGame{ false };
        void OnStartButtonPress();
        void OnDifficultyButtonPress();
        void OnQuitButtonPress();

        void SetDifficulty(Difficulty difficulty);

        bin::Text* m_DifficultyButtonText{};
    };
}  // namespace bout


#endif  // MAINMENU_H
