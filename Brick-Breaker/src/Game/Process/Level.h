#pragma once

#include <vector>

#include "GameObject/Brick.h"
#include "ResourceManager.h"

class GameLevel
{
public:
	GameLevel();
	void LoadLevel(const char* lvl_file, unsigned int level_width, unsigned int level_height);
	void Draw(SpriteRenderer* render);
	bool IsCompleted();
	std::vector<Brick>* GetBricks();
private:
	std::vector<Brick> bricks;

	void Init(std::vector<std::vector<unsigned int>>, unsigned int level_width, unsigned int level_height);
};