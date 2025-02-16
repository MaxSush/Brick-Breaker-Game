#include "MenuWindow.h"
#include "../../Window/KeyListner.h"

MenuWindow::MenuWindow()
	:
	rect(Rect({ 0,0 }, { 900,700 }))
{
	window_effect = new FrameBuffer(ResourceManager::GetShader("level_effects"), rect);
	ResourceManager::LoadTexture("assets/lose_menu.png", true, "lose_menu");
	ResourceManager::LoadTexture("assets/pause_menu.png", true, "pause_menu");
	ResourceManager::LoadTexture("assets/gamewin.png", true, "game_win");


	ResourceManager::LoadTexture("assets/MENU.png", true, "menu_button");
	ResourceManager::LoadTexture("assets/RESTART.png", true, "restart_button");
	ResourceManager::LoadTexture("assets/RESUME.png", true, "resume_button");
	ResourceManager::LoadTexture("assets/NEXT.png", true, "next_button");

}

MenuWindow::~MenuWindow()
{
	delete window_effect;
}

void MenuWindow::InitWindow_Effect(GameEffects* effects)
{
	window_effect->BeginRender();
	effects->Render(float(0));
}

void MenuWindow::DrawPauseWindow(SpriteRenderer* sprite)
{
	window_effect->EndRender();
	window_effect->Render();

	float offset = 100.0f;

	glm::vec2 resume_button_pos = { (rect.size.x / 2.0f) - 105, 170 + offset };
	glm::vec2 restart_button_pos = { (rect.size.x / 2.0f) - 105, resume_button_pos.y + offset };
	glm::vec2 menu_button_pos = { (rect.size.x / 2.0f) - 105, restart_button_pos.y + offset };

	sprite->DrawSprite(ResourceManager::GetTexture("pause_menu"), rect.pos, rect.size);

	sprite->DrawSprite(ResourceManager::GetTexture("resume_button"), resume_button_pos, { 210,60 }, glm::vec4(1.0f), (pause_itr == 1) ? scale : 1.0f);
	sprite->DrawSprite(ResourceManager::GetTexture("restart_button"), restart_button_pos, { 210,60 }, glm::vec4(1.0f), (pause_itr == 2) ? scale : 1.0f);
	sprite->DrawSprite(ResourceManager::GetTexture("menu_button"), menu_button_pos, { 210,60 }, glm::vec4(1.0f), (pause_itr == 3) ? scale : 1.0f);
}

void MenuWindow::DrawGameLoseWindow(SpriteRenderer* sprite)
{
	window_effect->EndRender();
	window_effect->Render();
	float offset = 100.0f;

	glm::vec2 restart_button_pos = { (rect.size.x / 2.0f) - 105, 200 + offset };
	glm::vec2 menu_button_pos = { (rect.size.x / 2.0f) - 105, restart_button_pos.y + offset };

	sprite->DrawSprite(ResourceManager::GetTexture("lose_menu"), rect.pos, rect.size);

	sprite->DrawSprite(ResourceManager::GetTexture("restart_button"), restart_button_pos, { 210,60 }, glm::vec4(1.0f), (lose_itr == 1) ? scale : 1.0f);
	sprite->DrawSprite(ResourceManager::GetTexture("menu_button"), menu_button_pos, { 210,60 }, glm::vec4(1.0f), (lose_itr == 2) ? scale : 1.0f);
}

void MenuWindow::DrawGameWinWindow(SpriteRenderer* sprite)
{
	window_effect->EndRender();
	window_effect->Render();
	sprite->DrawSprite(ResourceManager::GetTexture("game_win"), rect.pos, rect.size);
}

void MenuWindow::UpdatePauseMenu(float dt, GameWindow& state)
{
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_UP))
	{
		if (pause_itr == 1)
			pause_itr = 3;
		else
			pause_itr--;
		scale = 1.2f;
		ResourceManager::PlayAudio("player", false);
	}
	else if (KeyListner::IsKeyPressedOnce(GLFW_KEY_DOWN))
	{
		pause_itr++;
		if (pause_itr >= 4)
			pause_itr = 1;
		scale = 1.2f;
		ResourceManager::PlayAudio("player", false);
	}
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		if (pause_itr == 1)
			state = GameWindow::GAME_PLAY;
		if (pause_itr == 2)
			state = GameWindow::GAME_RESTART;
		if (pause_itr == 3)
			state = GameWindow::GAME_MENU;
		pause_itr = 1;
	}
}

void MenuWindow::UpdateLoseMenu(float dt, GameWindow& state)
{
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_UP))
	{
		if (lose_itr == 1)
			lose_itr = 2;
		else
			lose_itr--;
		scale = 1.2f;
		ResourceManager::PlayAudio("player", false);
	}
	else if (KeyListner::IsKeyPressedOnce(GLFW_KEY_DOWN))
	{
		lose_itr++;
		if (lose_itr >= 3)
			lose_itr = 1;
		scale = 1.2f;
		ResourceManager::PlayAudio("player", false);
	}
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		if (lose_itr == 1)
			state = GameWindow::GAME_RESTART;
		if (lose_itr == 2)
			state = GameWindow::GAME_MENU;
		lose_itr = 1;
	}
}

void MenuWindow::UpdateWinMenu(float dt, GameWindow& state)
{
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		state = GameWindow::GAME_MENU;
		ResourceManager::PlayAudio("player", false);
	}
}
