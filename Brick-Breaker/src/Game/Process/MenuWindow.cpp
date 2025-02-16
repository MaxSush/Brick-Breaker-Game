#include "MenuWindow.h"

MenuWindow::MenuWindow()
	:
	rect(Rect({ 200,200 }, { 500,300 }))
{
	window_effect = new FrameBuffer(Shader("assets/gamelvl_effects.vs","assets/gamelvl_effects.fg"), Rect(0, 0, 900, 700));
}

MenuWindow::~MenuWindow()
{
	delete window_effect;
}

void MenuWindow::DrawPauseWindow(SpriteRenderer* sprite)
{
	//window_effect->BeginRender();
	sprite->DrawSprite(ResourceManager::GetTexture("lvl_menu"), rect.pos, rect.size);
	//window_effect->EndRender();
	//window_effect->Render();
}

void MenuWindow::DrawGameOverWindow(SpriteRenderer* sprite)
{
}

void MenuWindow::DrawGameLoseWindow(SpriteRenderer* sprite)
{
}
