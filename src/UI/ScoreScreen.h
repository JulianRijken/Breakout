#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include <Node.h>

namespace bout
{
    class ScoreScreen final : public bin::Node, public bin::IEventListener
    {
    public:
        ScoreScreen();

    private:
        void ShowStats();
        void ExitScren();
    };

}  // namespace bout


#endif  // SCORESCREEN_H
