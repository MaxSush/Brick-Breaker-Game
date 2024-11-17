#pragma once

#include "GameObject.h"
#include "../Window/KeyListner.h"
#include "Utility/Rect.h"


class Ball : GameObject
{
	// coord is at top left corner
public:
	Ball(GLFWwindow* window, glm::vec2 pos, float radius, const Texture& texture);
	~Ball() { }
	void Draw(SpriteRenderer& render) override;
	void Update(float dt);
	void DoWallCollision(Rect& playzone);
	void SetBall();
	void ReboundX();
	void ReboundY();

	Rect& GetRect();
	glm::vec2& GetVelocity();
	float GetRadius() const;
	bool& IsStuck();

private:
	glm::vec2 velocity = glm::vec2(-1.0f);
	float radius;
	float speed = 300;
	bool stuck = true;
};