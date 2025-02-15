#pragma once
#include <Rect.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "TEXTURE.h"
#include "Manager/SpriteRenderer.h"
#include "Framebuffer.h"

struct Block {
	glm::vec2 pos, size;
	Texture texture;
};

class LevelMenu
{
public:
	LevelMenu();
	~LevelMenu();
	void Init();
	void LevelUpdate(float dt);
	void LevelRender();
	void GetGameState(GameState& state);
	int GetLevel();
private:
	GameState gamestate = GameState::GAME_LEVEL_MENU;
	Rect playzone;

	SpriteRenderer* sprite = nullptr;
	FrameBuffer* effects = nullptr;
	std::vector<Block> blocks;
	std::vector<float> scaleFactors;

	int total_blocks = 10;
	int selectedIndex = 0;
	float shift = 0.0f;

};