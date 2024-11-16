#include "Playfield.h"

#include <Brick.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "BoxCollider.h"


bout::Playfield::Playfield(glm::vec2 size) :
    m_Size(size)

{
    const int brickCount = static_cast<int>(std::floor(m_Size.x / 2.0f)) - 1;

    for(int y = 0; y < 5; ++y)
    {
        for(int x = -brickCount; x <= brickCount; ++x)
        {
            auto* brickPtr = bin::SceneGraph::AddNode<Brick>();
            brickPtr->SetParent(this);
            brickPtr->SetLocalPosition({ x, y });
        }
    }

    constexpr float wallWidth = 50.0f;

    auto* rightWallPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ wallWidth, m_Size.y + wallWidth * 2 });
    rightWallPtr->SetLocalPosition({ m_Size.x / 2.0f + wallWidth / 2.0f, 0 });
    rightWallPtr->SetParent(this);

    auto* leftWallPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ wallWidth, m_Size.y + wallWidth * 2 });
    leftWallPtr->SetLocalPosition({ -m_Size.x / 2.0f - wallWidth / 2.0f, 0 });
    leftWallPtr->SetParent(this);


    auto* topWallPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ m_Size.x, wallWidth });
    topWallPtr->SetLocalPosition({ 0, m_Size.y / 2.0f + wallWidth / 2.0f });
    topWallPtr->SetParent(this);
}

const glm::vec2& bout::Playfield::GetSize() const { return m_Size; }

void bout::Playfield::Draw()
{

    auto& renderer = bin::Locator::Get<bin::Renderer>();

    renderer.DrawWireBox(GetLocalPosition(), m_Size, { 0.5f, 0.5f }, { 217, 64, 237, 255 });
}
