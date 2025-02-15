#include "Level.h"

GameLevel::GameLevel()
{
}

void GameLevel::LoadLevel(int lvl, Rect playzone)
{
	std::string lvl_file = "assets/" + std::to_string(lvl) + "level.lvl";
	bricks.clear();
	unsigned int tilecode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(lvl_file);
	std::vector<std::vector<unsigned int>> tiledata;
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tilecode)
				row.push_back(tilecode);
			tiledata.push_back(row);
		}
		if (tiledata.size() > 0)
		{
			Init(tiledata, playzone);
		}
	}
}

void GameLevel::Draw(SpriteRenderer* render)
{
	for (auto& b : bricks)
	{
		if (!b.IsDestroyed())
		{
			b.Draw(render);
		}
	}
}

bool GameLevel::IsCompleted()
{
	for (const auto& b : bricks)
	{
		if (!b.IsSolid() && !b.IsDestroyed())
		{
			return false;
		}
	}
	return true;
}

std::vector<Brick>* GameLevel::GetBricks()
{
	return &bricks;
}

static float GetScale(float val)
{
	const float minVal = 5.0f, maxVal = 13.0f;
	const float minScale = 2.0f, maxScale = 4.0f;

	if (val > maxVal) 
		return minScale;  
	if (val < minVal) 
		return maxScale;  

	// Linear interpolation formula
	return minScale + ((maxVal - val) / (maxVal - minVal)) * (maxScale - minScale);
}


void GameLevel::Init(std::vector<std::vector<unsigned int>> tiledata, Rect playzone)
{
	float offset = 10.0f;
	const size_t height = tiledata.size();
	const size_t width = tiledata[0].size();


	const float unit_width	=	(playzone.Right - playzone.pos.x - (offset * 2)) / static_cast<float>(width);
	const float unit_height =	unit_width / 2.2f;

	/*
	*  0 ==> none
	*  1 ==> solid
	*  2 ==> blue
	*  3 ==> green
	*  4 ==> yellow
	*  5 ==> red
	*/

	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			if (tiledata[y][x] == 1)		// solid
			{
				glm::vec2 pos = glm::vec2(unit_width * x, unit_height * y) + playzone.pos + offset;
				glm::vec2 size(unit_width, unit_height);
				glm::vec4 color(glm::vec4(0.8f, 0.8f, 0.7f, 1.0f));
				Brick solid(ResourceManager::GetTexture("solid"), pos, size);
				solid.SetSolid();
				solid.SetColor(color);
				bricks.push_back(solid);
			}
			else if (tiledata[y][x] > 1)	// non-solid
			{
				glm::vec4 color = glm::vec4(1.0f); // original: white
				if (tiledata[y][x] == 2)
					color = glm::vec4(0.2f, 0.6f, 1.0f, 1.0f);
				else if (tiledata[y][x] == 3)
					color = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
				else if (tiledata[y][x] == 4)
					color = glm::vec4(0.8f, 0.8f, 0.4f, 1.0f);
				else if (tiledata[y][x] == 5)
					color = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);;

				glm::vec2 pos = glm::vec2(unit_width * x, unit_height * y) + playzone.pos + offset;
				glm::vec2 size(unit_width, unit_height);
				Brick brick(ResourceManager::GetTexture("brick"), pos, size);
				brick.SetColor(color);
				bricks.push_back(brick);
			}
		}
	}
}
