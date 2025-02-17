#include "MenuWindow.h"
#include "../../Window/KeyListner.h"
#include "../../Window/MouseListner.h"

MenuWindow::MenuWindow()
	:
	rect(Rect({ 0,0 }, { 900,700 })),
	pauseresume(Rect({ (rect.size.x / 2.0f) - 105, 170 + 100 }, { 210,60 })),
	pauserestart(Rect({ (rect.size.x / 2.0f) - 105, pauseresume.pos.y + 100 }, { 210,60 })),
	pausemenu(Rect({ (rect.size.x / 2.0f) - 105, pauserestart.pos.y + 100 }, { 210,60 })),

	loserestart(Rect({ (rect.size.x / 2.0f) - 105, 200 + 100 }, { 210,60 })),
	losemenu(Rect({ (rect.size.x / 2.0f) - 105, loserestart.pos.y + 100 }, { 210,60 }))
{
	window_effect = new FrameBuffer(ResourceManager::GetShader("level_effects"), rect);
	ResourceManager::LoadTexture("assets/lose_menu.png", true, "lose_menu");
	ResourceManager::LoadTexture("assets/pause_menu.png", true, "pause_menu");
	ResourceManager::LoadTexture("assets/gamewin.png", true, "game_win");

	ResourceManager::LoadTexture("assets/MENU.png", true, "menu_button");
	ResourceManager::LoadTexture("assets/RESTART.png", true, "restart_button");
	ResourceManager::LoadTexture("assets/RESUME.png", true, "resume_button");
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

	sprite->DrawSprite(ResourceManager::GetTexture("pause_menu"), rect.pos, rect.size);

	sprite->DrawSprite(ResourceManager::GetTexture("resume_button"), pauseresume.pos, pauseresume.size, glm::vec4(1.0f), (pause_itr == 1) ? scale : 1.0f);
	sprite->DrawSprite(ResourceManager::GetTexture("restart_button"), pauserestart.pos, pauserestart.size, glm::vec4(1.0f), (pause_itr == 2) ? scale : 1.0f);
	sprite->DrawSprite(ResourceManager::GetTexture("menu_button"), pausemenu.pos, pausemenu.size, glm::vec4(1.0f), (pause_itr == 3) ? scale : 1.0f);
}

void MenuWindow::DrawGameLoseWindow(SpriteRenderer* sprite)
{
	window_effect->EndRender();
	window_effect->Render();

	sprite->DrawSprite(ResourceManager::GetTexture("lose_menu"), rect.pos, rect.size);

	sprite->DrawSprite(ResourceManager::GetTexture("restart_button"), loserestart.pos, loserestart.size, glm::vec4(1.0f), (lose_itr == 1) ? scale : 1.0f);
	sprite->DrawSprite(ResourceManager::GetTexture("menu_button"), losemenu.pos, losemenu.size, glm::vec4(1.0f), (lose_itr == 2) ? scale : 1.0f);
}

void MenuWindow::DrawGameWinWindow(SpriteRenderer* sprite)
{
	window_effect->EndRender();
	window_effect->Render();
	sprite->DrawSprite(ResourceManager::GetTexture("game_win"), rect.pos, rect.size);
}

void MenuWindow::UpdatePauseMenu(float dt, GameWindow& state)
{
	// Pause Window Handle keyboard input (UP/DOWN navigation)
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

	// Pause Window Handle selection ENTER key mouse click input
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		if (pause_itr == 1)
			state = GameWindow::GAME_PLAY;
		else if (pause_itr == 2)
			state = GameWindow::GAME_RESTART;
		else if (pause_itr == 3)
			state = GameWindow::GAME_MENU;
		pause_itr = 1;
	}
	else if (MouseListner::IsButtonClickedOnce(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec mousepos = MouseListner::GetLastClickedMousePos();
		if (pauseresume.PointInRect(mousepos))
			state = GameWindow::GAME_PLAY;
		else if (pauserestart.PointInRect(mousepos))
			state = GameWindow::GAME_RESTART;
		else if( pausemenu.PointInRect(mousepos))
			state = GameWindow::GAME_MENU;
		pause_itr = 1;
	}

	// Pause Window Handle hover sound effect(Play audio only when hover state changes)
	int hoveredButton = -1;
	if (MouseListner::IsHoverOverRect(pauseresume))
		hoveredButton = 1;
	else if (MouseListner::IsHoverOverRect(pauserestart))
		hoveredButton = 2;
	else if (MouseListner::IsHoverOverRect(pausemenu))
		hoveredButton = 3;
	if (hoveredButton != -1 && hoveredButton != lastPHoveredButton) {
		ResourceManager::PlayAudio("player", false);
		pause_itr = hoveredButton;
	}
	lastPHoveredButton = hoveredButton;
}

void MenuWindow::UpdateLoseMenu(float dt, GameWindow& state)
{
	// Lose Window Handle keyboard navigation (UP/DOWN)
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_UP) || KeyListner::IsKeyPressedOnce(GLFW_KEY_DOWN)) {
		lose_itr = (lose_itr == 1) ? 2 : (lose_itr == 2 ? 1 : lose_itr);
		scale = 1.2f;
		ResourceManager::PlayAudio("player", false);
	}

	// Lose Window Handle selection ENTER key mouse click input
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		if (lose_itr == 1)
			state = GameWindow::GAME_RESTART;
		else if (lose_itr == 2)
			state = GameWindow::GAME_MENU;
		lose_itr = 1;
	}
	else if (MouseListner::IsButtonClickedOnce(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec mousepos = MouseListner::GetLastClickedMousePos();
		if (loserestart.PointInRect(mousepos))
			state = GameWindow::GAME_RESTART;
		else if (losemenu.PointInRect(mousepos))
			state = GameWindow::GAME_MENU;
		lose_itr = 1;
	}

	// Lose Window Handle hover sound effect (Play audio only when hover state changes)
	int hoveredButton = -1;
	if (MouseListner::IsHoverOverRect(loserestart))
		hoveredButton = 1;
	else if (MouseListner::IsHoverOverRect(losemenu))
		hoveredButton = 2;
	if (hoveredButton != -1 && hoveredButton != lastLHoveredButton) {
		ResourceManager::PlayAudio("player", false);
		lose_itr = hoveredButton;
	}
	lastLHoveredButton = hoveredButton;
}

void MenuWindow::UpdateWinMenu(float dt, GameWindow& state)
{
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		state = GameWindow::GAME_MENU;
		ResourceManager::PlayAudio("player", false);
	}
}
