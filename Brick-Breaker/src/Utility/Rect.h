#pragma once

#include <glm/glm.hpp>
#include <tuple>
#include <random>

enum class GameState
{
	GAME_MENU,
	GAME_LEVEL_MENU,
	GAME_ACTIVE,
	GAME_WIN,
	GAME_EXIT
};

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class Rect
{
public:
	float Left, Top, Right, Bottom = { 0 };
	glm::vec2 pos, size = { 0,0 };

	Rect(glm::vec2 pos, glm::vec2 size);
	Rect(float Left, float Top, float Right, float Bottom);
	glm::vec2 GetCenter() const;
	Collision CheckCollision(Rect& other, float radius);		// AABB - Circle collision
	bool CheckCollision(Rect& other) const;						// AABB - AABB collision
	Direction VectorDirection(glm::vec2 target);
	static std::mt19937 rng;
};
