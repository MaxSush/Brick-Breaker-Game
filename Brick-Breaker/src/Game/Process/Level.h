#pragma once

#include <vector>

#include "../GameObject/Brick.h"
#include "Manager/ResourceManager.h"

class GameLevel
{
public:
	GameLevel(int level);
	void LoadLevel(Rect playzone);
	void Draw(SpriteRenderer* render);
	bool IsCompleted();
	std::vector<Brick>* GetBricks();
private:
	std::vector<Brick> bricks;
	int cur_level;
	void Init(std::vector<std::vector<unsigned int>>, Rect playzone);
};