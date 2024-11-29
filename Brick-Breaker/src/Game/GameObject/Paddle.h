#pragma once

#include "GameObject.h"
#include "Ball.h"
#include "Utility/Rect.h"
#include "Utility/Texture.h"

class Paddle : GameObject
{
public:
	Paddle(const Texture& texture, glm::vec2 pos, glm::vec2 size);
	~Paddle();
	void Update(float dt, Rect& playzone, Ball* ball);
	void DoBallCollision(Ball* ball);
	void Draw(SpriteRenderer* render) override;
	void SetCooldown();
private:
	glm::vec2 velocity = { 0,0 };
	float speed = 550;
	bool cooldown = false;

	void DoWallCollision(Rect& playzone, Ball* ball);
};