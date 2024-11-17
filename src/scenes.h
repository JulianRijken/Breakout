#ifndef SCENES_H
#define SCENES_H

namespace bout::scenes
{
    enum class Name
    {
        Game,
        MainMenu
    };

    void LoadScene(Name name);
}  // namespace bout::scenes
#endif  // SCENES_H
