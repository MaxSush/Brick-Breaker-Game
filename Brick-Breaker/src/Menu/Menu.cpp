#include "Menu.h"
#include "Menu.h"
#include "Menu.h"
#include <iostream>
#include "../Window/KeyListner.h"
#include "../Window/MouseListner.h"

Menu::Menu()
	:
	playzone(Rect(0, 0, 900, 700)),
	play_button(Rect({ (playzone.size.x / 2.0f) - 130, playzone.size.y - (130 * 2) }, { 270,50 })),
	exit_button(Rect({ (playzone.size.x / 2.0f) - 130, playzone.size.y - (160) }, { 270, 50 }))
{
}

Menu::~Menu()
{
	delete sprite;
}

void Menu::Init()
{
	ResourceManager::LoadTexture("assets/menu.jpg", false, "menu");
	ResourceManager::LoadTexture("assets/menu_play.png", true, "button_play");
	ResourceManager::LoadTexture("assets/menu_exit.png", true, "button_exit");

	ResourceManager::LoadAudio("assets/menu.wav", "menu_audio");

	sprite = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Menu::Update(float dt)
{
	if (itr == 0) 
	{
		scale_play = 1.2f;
		scale_exit = std::max(scale_exit - dt, 1.0f);
	}
	else if (itr == 1) 
	{
		scale_exit = 1.2f;
		scale_play = std::max(scale_play - dt, 1.0f);
	}

	ButtonUpdate();
	ResourceManager::PlayAudio("menu_audio", true);
}

void Menu::Render()
{
	sprite->DrawSprite(ResourceManager::GetTexture("menu"), playzone.pos, playzone.size);
	sprite->DrawSprite(ResourceManager::GetTexture("button_play"), play_button.pos, play_button.size, glm::vec4(1.0f), scale_play);
	sprite->DrawSprite(ResourceManager::GetTexture("button_exit"), exit_button.pos, exit_button.size, glm::vec4(1.0f), scale_exit);
}

void Menu::GetGameState(GameState& state)
{
	state = gamestate;
	gamestate = GameState::GAME_MENU;
}

void Menu::ButtonUpdate()
{
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_UP) || KeyListner::IsKeyPressedOnce(GLFW_KEY_DOWN)) {
		itr = 1 - itr;
		ResourceManager::PlayAudio("player", false);
	}

	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
		gamestate = (itr == 0) ? GameState::GAME_LEVEL_MENU : GameState::GAME_EXIT;

	if (MouseListner::IsButtonClickedOnce(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mousepos = MouseListner::GetLastClickedMousePos();
		if (play_button.PointInRect(mousepos)) 
			gamestate = GameState::GAME_LEVEL_MENU;
		else if (exit_button.PointInRect(mousepos))
			gamestate = GameState::GAME_EXIT;
	}

	int hoveredButton = -1;
	if (MouseListner::IsHoverOverRect(play_button)) 
		hoveredButton = 0;
	else if (MouseListner::IsHoverOverRect(exit_button)) 
		hoveredButton = 1;
	if (hoveredButton != -1 && hoveredButton != lastHoveredButton) {
		ResourceManager::PlayAudio("player", false);
		itr = hoveredButton;
	}
	lastHoveredButton = hoveredButton;
}