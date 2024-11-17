#pragma once

#include <glm/glm.hpp>

class Rect
{
public:
	float Left, Top, Right, Bottom = { 0 };
	glm::vec2 pos, size = { 0,0 };

	Rect(glm::vec2 pos, glm::vec2 size);
	bool CheckCollision(Rect& other, float radius) const;		// AABB - Circle collision
	bool CheckCollision(Rect& other) const;						// AABB - AABB collision
};
