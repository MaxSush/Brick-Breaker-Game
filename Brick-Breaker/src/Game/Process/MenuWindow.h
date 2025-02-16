#pragma once
#include <Rect.h>
#include "Manager/Framebuffer.h"
#include <Manager/SpriteRenderer.h>
#include "GamePostProcessing.h"

class MenuWindow
{
public:
	MenuWindow();
	~MenuWindow();
	void InitWindow_Effect(GameEffects* effects);
	void DrawPauseWindow(SpriteRenderer* sprite);
	void DrawGameWinWindow(SpriteRenderer* sprite);
	void DrawGameLoseWindow(SpriteRenderer* sprite);
	void UpdatePauseMenu(float dt, GameWindow& state);
	void UpdateLoseMenu(float dt, GameWindow& state);
	void UpdateWinMenu(float dt, GameWindow& state);


private:
	FrameBuffer* window_effect = nullptr;
	Rect rect;

	int pause_itr = 1;
	int lose_itr = 1;

	float scale = 1.2f;
};