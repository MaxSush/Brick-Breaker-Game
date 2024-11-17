#include "Rect.h"

Rect::Rect(glm::vec2 pos, glm::vec2 size)
	: pos(pos), size(size)
{
	Left = pos.x;
	Right = pos.x + size.x;
	Top = pos.y;
	Bottom = pos.y + size.y;
}

bool Rect::CheckCollision(Rect& other, float radius) const
{
	float ballCenter = this->pos.x + radius;

	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(other.size.x / 2.0f, other.size.y / 2.0f);
	glm::vec2 aabb_center(other.pos.x + aabb_half_extents.x,
		other.pos.y + aabb_half_extents.y);

	// get difference vector between both centers
	glm::vec2 difference = ballCenter - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	// add clamped value to AABB_center and get the value closest to circle
	glm::vec2 closest = aabb_center + clamped;

	// vector between center circle and closest point AABB
	difference = closest - ballCenter;

	return glm::length(difference) < radius;
}

bool Rect::CheckCollision(Rect& other) const
{
	// collision x-axis?
	bool collisionX = this->pos.x + this->size.x >= other.pos.x &&
		other.pos.x + other.size.x >= this->pos.x;
	// collision y-axis?
	bool collisionY = this->pos.y + this->size.y >= other.pos.y &&
		other.pos.y + other.size.y >= this->pos.y;
	// collision only if on both axes
	return collisionX && collisionY;
}
