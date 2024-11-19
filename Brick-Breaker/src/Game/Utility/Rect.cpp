#include "Rect.h"
#include "Rect.h"

Rect::Rect(glm::vec2 pos, glm::vec2 size)
	: pos(pos), size(size)
{
	Left = pos.x;
	Right = pos.x + size.x;
	Top = pos.y;
	Bottom = pos.y + size.y;
}

glm::vec2 Rect::GetCenter() const
{
	return glm::vec2(Left + size.x / 2.0f, Top + size.y / 2.0f);
}

Collision Rect::CheckCollision(Rect& ball, float radius)
{
	glm::vec2 center(ball.pos + radius);

	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(size.x / 2.0f, size.y / 2.0f);
	glm::vec2 aabb_center(pos.x + aabb_half_extents.x,
		pos.y + aabb_half_extents.y);

	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	// add clamped value to AABB_center and get the value closest to circle
	glm::vec2 closest = aabb_center + clamped;

	// vector between center circle and closest point AABB
	difference = closest - center;

	if (glm::length(difference) <= radius)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
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

Direction Rect::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}
