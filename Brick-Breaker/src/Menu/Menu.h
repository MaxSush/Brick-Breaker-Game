#pragma once

#include "Manager/SpriteRenderer.h"
#include "Manager/ResourceManager.h"
#include "Rect.h"

class Menu
{
public:
	Menu();
	~Menu();
	void Init();
	void Update(float dt);
	void Render();

	void GetGameState(GameState& state);
	void ButtonUpdate();
private:
	SpriteRenderer* sprite = nullptr;
	Rect playzone;

	float scale_play = 1.0f; 
	float scale_exit = 1.0f;
	unsigned int itr = 0;
	int lastHoveredButton = -1;

	Rect exit_button;
	Rect play_button;

	GameState gamestate = GameState::GAME_MENU;
};