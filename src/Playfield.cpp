#include "Playfield.h"

#include <MathExtensions.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "Brick.h"
#include "Prefabs.h"
#include "Sprite.h"
#include "TweenEngine.h"
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

            // Make bricks fall :O
            bin::TweenEngine::Start({ .delay = spawnPosition.y * 0.2f,
                                      .duration = 1.5f + bin::math::RandomValue() * 0.2f,
                                      .easeType = bin::EaseType::BounceOut,
                                      .onUpdate =
                                          [brickSpawned, spawnPosition](float value)
                                      {
                                          const float fromPosition = 10.0f;
                                          const float fallHeight = std::lerp(fromPosition, spawnPosition.y, value);
                                          brickSpawned->SetLocalPosition({ spawnPosition.x, fallHeight });
                                      } },
                                    *brickSpawned);
        }
    }

    auto& rightWall = bin::SceneGraph::AddNode<Wall>(glm::vec2{ 1, 0 });
    rightWall.SetParent(this);
    rightWall.SetLocalScale({ WALL_WIDTH, 0.0f });
    rightWall.SetLocalPosition({ m_Size.x / 2.0f + WALL_WIDTH / 2.0f, 0 });
    m_RightWallSpritePtr = rightWall.GetFirstChildNodeOfType<bin::Sprite>();

    auto& leftWall = bin::SceneGraph::AddNode<Wall>(glm::vec2{ -1, 0 });
    leftWall.SetParent(this);
    leftWall.SetLocalScale({ WALL_WIDTH, 0.0f });
    leftWall.SetLocalPosition({ -m_Size.x / 2.0f - WALL_WIDTH / 2.0f, 0 });
    m_LeftWallSpritePtr = leftWall.GetFirstChildNodeOfType<bin::Sprite>();

    m_TopWallPtr = &bin::SceneGraph::AddNode<Wall>(glm::vec2{ 0, 1 });
    m_TopWallPtr->SetParent(this);
    m_TopWallPtr->SetLocalPosition({ 0, m_Size.y / 2.0f + WALL_WIDTH / 2.0f });
    m_TopWallPtr->SetLocalScale({ m_Size.x, 0.0f });


    // Mode side walls inwards
    bin::TweenEngine::Start({ .duration = 0.8f,
                              .easeType = bin::EaseType::SineOut,
                              .onUpdate =
                                  [this, &rightWall, &leftWall](float value)
                              {
                                  const glm::vec2 fromSale = { 0.0f, m_Size.y + WALL_WIDTH * 2 };
                                  const glm::vec2 toScale = { WALL_WIDTH, fromSale.y };
                                  const glm::vec2 mixedScale = glm::mix(fromSale, toScale, value);

                                  rightWall.SetLocalScale(mixedScale);
                                  leftWall.SetLocalScale(mixedScale);
                              } },
                            *this);

    // Move top wall down
    bin::TweenEngine::Start(
        { .delay = 0.8f,
          .duration = 1.5f,
          .easeType = bin::EaseType::SineOut,
          .onUpdate =
              [this](float value) {
                  m_TopWallPtr->SetLocalScale({ m_TopWallPtr->GetLocalScale().x, value * WALL_WIDTH });
              } },
        *this);
}

const glm::vec2& bout::Playfield::GetSize() const { return m_Size; }

void bout::Playfield::LateUpdate()
{
    // This is probably the most hacky thing about the project...
    // So the top wall needs to scale exactly to match the side walls!
    // Yes all this is needed because I want transparency and
    // my gf does not want a gap in the walls :(

    const float leftWallPosition =
        m_LeftWallSpritePtr->GetWorldPosition().x + m_LeftWallSpritePtr->GetWorldScale().x / 2.0f;
    const float rightWallPosition =
        m_RightWallSpritePtr->GetWorldPosition().x - m_RightWallSpritePtr->GetWorldScale().x / 2.0f;

    const float center = std::lerp(leftWallPosition, rightWallPosition, 0.5f);
    const float distance = rightWallPosition - leftWallPosition;

    m_TopWallPtr->SetLocalScale({ distance, m_TopWallPtr->GetLocalScale().y });
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
