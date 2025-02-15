#include "Menu.h"
#include "Menu.h"
#include "Menu.h"
#include <iostream>
#include "../Window/KeyListner.h"

Menu::Menu()
	:
	playzone(Rect(0, 0, 900, 700))
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
		scale_play = 1.2f;
	else if (itr == 1)
		scale_exit = 1.2f;

	if (scale_play > 1.0f)
		scale_play -= dt;
	if (scale_exit > 1.0f)
		scale_exit -= dt;
	ButtonUpdate();

	ResourceManager::PlayAudio("menu_audio", true);
}

void Menu::Render()
{
	Rect play_button({ (playzone.size.x / 2.0f) - 130, playzone.size.y - (130 * 2) }, { 270,130 });
	Rect exit_button({ (playzone.size.x / 2.0f) - 130, playzone.size.y - (160) }, { 270, 130 });
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
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_UP))
	{
		if (itr == 0)
			itr = 1;
		else
			itr--;
		ResourceManager::PlayAudio("player", false);
	}
	else if (KeyListner::IsKeyPressedOnce(GLFW_KEY_DOWN))
	{
		itr++;
		if (itr > 1)
			itr = 0;
		ResourceManager::PlayAudio("player", false);
	}

	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		gamestate = (itr == 0) ? GameState::GAME_LEVEL_MENU : GameState::GAME_EXIT;
	}
}