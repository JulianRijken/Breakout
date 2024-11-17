#include "Playfield.h"

#include <Brick.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "BoxCollider.h"
#include "Prefabs.h"


bout::Playfield::Playfield(const glm::vec2& size) :
    m_Size(size)

{
    const int brickCount = 11;
    const glm::vec2 brickSize = { 1.8f, 0.8f };
    const glm::vec2 brickPadding = { 0.3f, 0.3f };

    for(int y = 0; y < 5; ++y)
    {
        glm::vec2 spawnPositon{};
        spawnPositon.y = y * (brickPadding.y + brickSize.y);

        for(int x = 0; x < brickCount; ++x)
        {
            const float centerdIndexX = static_cast<float>((brickCount - 1) / 2.0f) - x;

            spawnPositon.x = centerdIndexX * (brickPadding.x + brickSize.x);

            switch(y)
            {
                case 0:
                    bout::prefabs::BlueBrick(brickSize, *this).SetLocalPosition(spawnPositon);
                    break;
                case 1:
                    bout::prefabs::GreenBrick(brickSize, *this).SetLocalPosition(spawnPositon);
                    break;
                case 2:
                    bout::prefabs::YellowBrick(brickSize, *this).SetLocalPosition(spawnPositon);
                    break;
                case 3:
                    bout::prefabs::OrangeBrick(brickSize, *this).SetLocalPosition(spawnPositon);
                    break;
                case 4:
                    bout::prefabs::RedBrick(brickSize, *this).SetLocalPosition(spawnPositon);
                    break;
            }
        }
    }

    constexpr float wallWidth = 50.0f;

    auto& rightWall = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ wallWidth, m_Size.y + wallWidth * 2 });
    rightWall.SetLocalPosition({ m_Size.x / 2.0f + wallWidth / 2.0f, 0 });
    rightWall.SetParent(this);

    auto& leftWall = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ wallWidth, m_Size.y + wallWidth * 2 });
    leftWall.SetLocalPosition({ -m_Size.x / 2.0f - wallWidth / 2.0f, 0 });
    leftWall.SetParent(this);


    auto& topWall = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ m_Size.x, wallWidth });
    topWall.SetLocalPosition({ 0, m_Size.y / 2.0f + wallWidth / 2.0f });
    topWall.SetParent(this);
}

const glm::vec2& bout::Playfield::GetSize() const { return m_Size; }

void bout::Playfield::Draw(const bin::Renderer&)
{
    // auto& renderer = bin::Locator::Get<bin::Renderer>();
    // renderer.DrawWireBox(GetLocalPosition(), m_Size, { 0.5f, 0.5f }, { 217, 64, 237, 255 });
}
