#pragma once

#include <vector>

#include "../GameObject/Brick.h"
#include "Manager/ResourceManager.h"

class GameLevel
{
public:
	GameLevel();
	void LoadLevel(int lvl, Rect playzone);
	void Draw(SpriteRenderer* render);
	bool IsCompleted();
	std::vector<Brick>* GetBricks();
private:
	std::vector<Brick> bricks;

	void Init(std::vector<std::vector<unsigned int>>, Rect playzone);
};