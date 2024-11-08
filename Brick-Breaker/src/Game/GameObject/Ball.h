#pragma once

#include "GameObject.h"

class Ball : GameObject
{
	// ball's position is equal to its center position
public:
	Ball(GLFWwindow* window, glm::vec2 pos, float radius, const Texture& texture);
	void Draw(SpriteRenderer& render) override;
	void Update(float dt);
	void SetBall();

private:
	glm::vec2 velocity = glm::vec2(0.0f);
	float radius;
	float speed = 10;
	bool stuck = true;
};