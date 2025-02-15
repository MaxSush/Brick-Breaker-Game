#pragma once

#include "GameObject.h"
#include "../Window/KeyListner.h"
#include "Rect.h"
#include "Brick.h"

class Ball : GameObject
{
	// coord is at top left corner
public:
	Ball(glm::vec2 pos, float radius, const Texture& texture);
	~Ball() { }
	void Draw(SpriteRenderer* render) override;
	void Update(float dt);
	bool DoWallCollision(Rect& playzone);
	void DoBrickColision(Collision& collision);
	void SetBall();
	void ReboundX();
	void ReboundY();
	void Reset();

	Rect& GetRect();
	glm::vec2& GetVelocity();
	void SetVelocity(glm::vec2 new_vel);
	float GetRadius() const;
	bool& IsStuck();
	void SetSpeed(float multiplier);

	bool stuck = true;
	bool pass_through = false;
private:
	glm::vec2 velocity = { 0.0f,-1.0f };
	float radius;
	float speed = 600;
};