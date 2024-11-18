#include "Playfield.h"

#include <fmt/core.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "BoxCollider.h"
#include "Brick.h"
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

            Brick* brickSpawned{ nullptr };

            switch(y)
            {
                case 0:
                    brickSpawned = &bout::prefabs::BlueBrick(brickSize, *this);
                    break;
                case 1:
                    brickSpawned = &bout::prefabs::GreenBrick(brickSize, *this);
                    break;
                case 2:
                    brickSpawned = &bout::prefabs::YellowBrick(brickSize, *this);
                    break;
                case 3:
                    brickSpawned = &bout::prefabs::OrangeBrick(brickSize, *this);
                    break;
                case 4:
                    brickSpawned = &bout::prefabs::RedBrick(brickSize, *this);
                    break;
            }

            assert(brickSpawned != nullptr && "Brick does not exist");


            brickSpawned->SetLocalPosition(spawnPositon);
            brickSpawned->m_OnDestroyedEvent.AddListener(this, &Playfield::OnBrickDestroyedEvent);
            m_Bricks.insert(brickSpawned);
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
    // renderer.DrawWireBox(GetLocalPosition(), m_Size, { 0.5f, 0.5f }, { 217, 64, 237, 255 });
}

void bout::Playfield::OnBrickDestroyedEvent(Node& brick)
{
    auto* brickPtr = dynamic_cast<Brick*>(&brick);
    assert(brickPtr != nullptr);

    m_Bricks.erase(brickPtr);

    if(m_Bricks.empty())
        OnPlayfieldCleared();
}

void bout::Playfield::OnPlayfieldCleared() { m_OnFieldCleared.Invoke(); }
