#pragma once
#include <Rect.h>
#include "Manager/Framebuffer.h"
#include <Manager/SpriteRenderer.h>

class MenuWindow
{
public:
	MenuWindow();
	~MenuWindow();
	void DrawPauseWindow(SpriteRenderer* sprite);
	void DrawGameOverWindow(SpriteRenderer* sprite);
	void DrawGameLoseWindow(SpriteRenderer* sprite);
private:
	FrameBuffer* window_effect = nullptr;
	Rect rect;
};