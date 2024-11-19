#include "Playfield.h"

#include <Renderer.h>
#include <SceneGraph.h>

#include <iostream>

#include "Brick.h"
#include "Prefabs.h"
#include "Sprite.h"
#include "Wall.h"


bout::Playfield::Playfield(const glm::vec2& size) :
    m_Size(size)

{
    constexpr int brickCount = 11;
    constexpr glm::vec2 brickSize = { 1.8f, 0.8f };
    constexpr glm::vec2 brickPadding = { 0.3f, 0.3f };

    for(int y = 0; y < 5; ++y)
    {
        glm::vec2 spawnPosition{};
        spawnPosition.y = static_cast<float>(y) * (brickPadding.y + brickSize.y);

        for(int x = 0; x < brickCount; ++x)
        {
            const float centeredIndexX = static_cast<float>((brickCount - 1)) / 2.0f - static_cast<float>(x);

            spawnPosition.x = centeredIndexX * (brickPadding.x + brickSize.x);

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

            brickSpawned->SetLocalPosition(spawnPosition);
            brickSpawned->m_OnDestroyedEvent.AddListener(this, &Playfield::OnBrickDestroyedEvent);
            m_BrickPtrs.insert(brickSpawned);
        }
    }

    auto& rightWall = bin::SceneGraph::AddNode<Wall>(glm::vec2{ 1, 0 });
    rightWall.SetParent(this);
    rightWall.SetLocalScale({ WALL_WIDTH, m_Size.y + WALL_WIDTH * 2 });
    rightWall.SetLocalPosition({ m_Size.x / 2.0f + WALL_WIDTH / 2.0f, 0 });
    m_RightWallSpritePtr = rightWall.GetFirstChildNodeOfType<bin::Sprite>();

    auto& leftWall = bin::SceneGraph::AddNode<Wall>(glm::vec2{ -1, 0 });
    leftWall.SetParent(this);
    leftWall.SetLocalScale({ WALL_WIDTH, m_Size.y + WALL_WIDTH * 2 });
    leftWall.SetLocalPosition({ -m_Size.x / 2.0f - WALL_WIDTH / 2.0f, 0 });
    m_LeftWallSpritePtr = leftWall.GetFirstChildNodeOfType<bin::Sprite>();

    m_TopWallPtr = &bin::SceneGraph::AddNode<Wall>(glm::vec2{ 0, 1 });
    m_TopWallPtr->SetParent(this);
    m_TopWallPtr->SetLocalPosition({ 0, m_Size.y / 2.0f + WALL_WIDTH / 2.0f });
    m_TopWallPtr->SetLocalScale({ m_Size.x, WALL_WIDTH });
}

const glm::vec2& bout::Playfield::GetSize() const { return m_Size; }

void bout::Playfield::LateUpdate()
{
    // This is probably the most hacky thing the bout project...
    // So the top wall needs to scale exactly to match the side walls!
    // Yes all this is needed because I want transparenty and
    // my gf does not want a gap in the walls :(

    const float leftWallPosition =
        m_LeftWallSpritePtr->GetWorldPosition().x + m_LeftWallSpritePtr->GetWorldScale().x / 2.0f;
    const float rightWallPosition =
        m_RightWallSpritePtr->GetWorldPosition().x - m_RightWallSpritePtr->GetWorldScale().x / 2.0f;

    const float center = std::lerp(leftWallPosition, rightWallPosition, 0.5f);

    const float dist = rightWallPosition - leftWallPosition;
    std::cout << dist << std::endl;

    m_TopWallPtr->SetLocalScale({ dist, WALL_WIDTH });
    m_TopWallPtr->SetWorldPosition({ center, m_TopWallPtr->GetWorldPosition().y });
}

void bout::Playfield::OnBrickDestroyedEvent(Node& brick)
{
    auto* brickPtr = dynamic_cast<Brick*>(&brick);
    assert(brickPtr != nullptr);

    m_BrickPtrs.erase(brickPtr);

    if(m_BrickPtrs.empty())
        OnPlayfieldCleared();
}

void bout::Playfield::OnPlayfieldCleared() { m_OnFieldCleared.Invoke(); }
