#pragma once

#include "GameObject.h"
#include "Ball.h"
#include "Rect.h"
#include "Texture.h"

class Paddle : GameObject
{
public:
	Paddle(const Texture& texture, glm::vec2 pos, glm::vec2 size);
	~Paddle();
	void Update(float dt, Rect& playzone, Ball* ball);
	void DoBallCollision(Ball* ball);
	void Draw(SpriteRenderer* render) override;
	void SetCooldown();
	void Reset();
	Rect& GetRect();
private:
	glm::vec2 start_pos, start_size;
	bool cooldown = false;

	void DoWallCollision(Rect& playzone, Ball* ball);
};