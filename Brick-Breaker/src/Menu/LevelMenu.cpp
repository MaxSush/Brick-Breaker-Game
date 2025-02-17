#include "LevelMenu.h"
#include <iostream>
#include "Manager/ResourceManager.h"
#include "../Window/KeyListner.h"
#include "../Window/MouseListner.h"

LevelMenu::LevelMenu()
	:
	playzone(Rect(0, 0, 900, 700)),
	cancel(Rect({ 830,20 }, { 50,45 })),
	play(Rect({ 400,530 }, { 130,118.8f }))
{
	ResourceManager::LoadShader("assets/gamelvl_effects.vs", "assets/gamelvl_effects.fg", "level_effects");
	scaleFactors.resize(total_blocks, 1.0f);
}

LevelMenu::~LevelMenu()
{
	delete effects;
	delete sprite;
}

void LevelMenu::Init()
{
	ResourceManager::LoadTexture("assets/lvl_menu.jpg", false, "lvl_menu");
	ResourceManager::LoadTexture("assets/cancel.png", true, "cancel");
	ResourceManager::LoadTexture("assets/play.png", true, "play");

	ResourceManager::LoadAudio("assets/scroll.wav", "scroll");

	for (int i = 1; i <= total_blocks; i++)
	{
		std::string name = "assets/" + std::to_string(i) + "level.png";
		ResourceManager::LoadTexture(name.c_str(), true, std::to_string(i) + "level");
	}

	sprite = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	effects = new FrameBuffer(ResourceManager::GetShader("level_effects"), Rect(0, 0, 900, 700));

	float offset = 150.0f;
	glm::vec2 size = { 300, 200 };
	for (int i = 0; i < total_blocks; i++)
	{
		Block block;
		block.pos = { i * (size.x + offset), (700 / 2.3f) - (size.y / 2.0f) };
		block.size = size;
		block.texture = ResourceManager::GetTexture(std::to_string(i + 1) + "level");
		blocks.push_back(block);
	}
}

void LevelMenu::LevelUpdate(float dt)
{
	float target_shift = -blocks[selectedIndex].pos.x + 300.0f;
	shift = glm::mix(shift, target_shift, 0.08f);
	ResourceManager::PlayAudio("menu_audio", true);
	ProcessInput(dt);
}

void LevelMenu::ProcessInput(float dt)
{
	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_RIGHT))
	{
		selectedIndex = std::min(selectedIndex + 1, total_blocks - 1);
	}
	else if (KeyListner::IsKeyPressedOnce(GLFW_KEY_LEFT))
	{
		selectedIndex = std::max(selectedIndex - 1, 0);
	}

	if (KeyListner::IsKeyPressedOnce(GLFW_KEY_BACKSPACE))
	{
		gamestate = GameState::GAME_MENU;
	}

	if (MouseListner::IsButtonClickedOnce(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec mousepos = MouseListner::GetLastClickedMousePos();
		if (cancel.PointInRect(mousepos))
			gamestate = GameState::GAME_MENU;
		else if (play.PointInRect(mousepos))
		{
			StartGame();
		}
	}
	else if (KeyListner::IsKeyPressedOnce(GLFW_KEY_ENTER))
	{
		StartGame();
	}
	
	if (MouseListner::IsWheelScrolled())
	{
		int newSelectedIndex = selectedIndex + MouseListner::WheelScrolledDirection();
		newSelectedIndex = std::clamp(newSelectedIndex, 0, total_blocks - 1);

		if (newSelectedIndex != lastSelectedIndex)
		{
			selectedIndex = newSelectedIndex;
			ResourceManager::PlayAudio("scroll", false);
			lastSelectedIndex = selectedIndex;
		}
	}
}

void LevelMenu::LevelRender()
{
	effects->BeginRender();
	sprite->DrawSprite(ResourceManager::GetTexture("lvl_menu"), playzone.pos, playzone.size, glm::vec4(1.0f));
	effects->EndRender();
	effects->Render();
	for (int i = 0; i < total_blocks; i++)
	{
		Block bck = blocks[i];
		bck.pos.x += shift;

		scaleFactors[i] = glm::mix(scaleFactors[i], (i == selectedIndex) ? 1.5f : 1.0f, 0.08f);
		glm::vec4 color = (i == selectedIndex) ? glm::vec4(1.0f) : glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

		sprite->DrawSprite(bck.texture, bck.pos, bck.size, color, scaleFactors[i]);
	}
	sprite->DrawSprite(ResourceManager::GetTexture("cancel"), cancel.pos, cancel.size, glm::vec4(1.0f));
	sprite->DrawSprite(ResourceManager::GetTexture("play"), play.pos, play.size, glm::vec4(1.0f));
}

void LevelMenu::GetGameState(GameState& state)
{
	state = gamestate;
	gamestate = GameState::GAME_LEVEL_MENU;
}

int LevelMenu::GetLevel()
{
	return level;
}

void LevelMenu::StartGame()
{
	gamestate = GameState::GAME_ACTIVE;
	ResourceManager::PauseAudio("menu_audio");
	level = selectedIndex + 1;
}

