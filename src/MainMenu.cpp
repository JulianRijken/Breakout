#include "MainMenu.h"

#include <Button.h>
#include <Font.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Text.h>
#include <Texture.h>
#include <Tween.h>

#include "GlobalSettings.h"
#include "Prefabs.h"


bout::MainMenu::MainMenu()
{
    auto& camera = bin::SceneGraph::AddNode<bin::Camera>();
    camera.SetOrthoSize(10);

    auto& title = bin::SceneGraph::AddNode<bin::Text>(
        "BREAKOUT", bin::Resources::GetFont(FontName::NES_Font), glm::vec2{ 0.5f, 0.5f }, 2.0f);
    title.SetParent(this);
    title.SetLocalPosition({ 0, 6 });

    auto& startButton = prefabs::TextButton({ 10, 2 }, "START", *this);
    startButton.SetParent(this);
    startButton.SetLocalPosition({ 0, 2 });
    startButton.m_OnPress.AddListener(this, &MainMenu::OnStartButtonPress);

    auto& quitButton = prefabs::TextButton({ 10, 2 }, "QUIT", *this);
    quitButton.SetParent(this);
    quitButton.SetLocalPosition({ 0, -2 });
    quitButton.m_OnPress.AddListener(this, &MainMenu::OnQuitButtonPress);
}

void bout::MainMenu::OnStartButtonPress() { bin::SceneGraph::LoadScene(SceneName::Game); }

void bout::MainMenu::OnQuitButtonPress() { SDL_Quit(); }
