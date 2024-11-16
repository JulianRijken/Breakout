#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <Node.h>

namespace bout
{
    class Playfield final : public bin::Node
    {

    public:
        Playfield(const glm::vec2& size);

        [[nodiscard]] const glm::vec2& GetSize() const;

    private:
        void Draw() override;

        glm::vec2 m_Size{};
    };
}  // namespace bout


#endif  // PLAYFIELD_H
