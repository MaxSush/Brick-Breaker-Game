#include "Ball.h"

Ball::Ball(GLFWwindow* window, glm::vec2 pos, float radius, const Texture& texture)
	:
	GameObject(window, pos - radius, glm::vec2(radius * 2), texture),
	radius(radius)
{
}

void Ball::Draw(SpriteRenderer& render)
{
	render.DrawSprite(texture, pos, size);
}

void Ball::Update(float dt)
{
}

void Ball::SetBall()
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		stuck = false;
	}
}
