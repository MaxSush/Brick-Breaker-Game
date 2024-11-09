#include "Ball.h"


Ball::Ball(GLFWwindow* window, glm::vec2 pos, float radius, const Texture& texture)
	:
	GameObject(window, pos, glm::vec2(radius * 2), texture),
	radius(radius)
{
}

void Ball::Draw(SpriteRenderer& render)
{
	render.DrawSprite(texture, pos, size);
}

void Ball::Update(float dt)
{
	if (!stuck)
	{
		pos += glm::normalize(velocity) * speed * dt;
	}
}

void Ball::DoWallCollision(Rect& playzone)
{
	if (!stuck)
	{
		if (pos.x <= playzone.Left)
		{
			velocity.x = -velocity.x;
			pos.x = playzone.Left;
		}
		else if ((pos.x + size.x) >= playzone.Right)
		{
			velocity.x = -velocity.x;
			pos.x = playzone.Right - size.x;
		}

		if (pos.y <= playzone.Top)
		{
			velocity.y = -velocity.y;
			pos.y = playzone.Top;
		}
		else if ((pos.y + size.y) >= playzone.Bottom)
		{
			velocity.y = -velocity.y;
			pos.y = playzone.Bottom - size.y;
		}

	}
}

void Ball::SetBall()
{
	if (KeyListner::isKeyPressed(GLFW_KEY_SPACE))
	{
		stuck = false;
	}
}

const glm::vec2 Ball::GetVelocity() const
{
	return velocity;
}

const glm::vec2 Ball::GetPosition() const
{
	return pos;
}

const float Ball::GetSpeed() const
{
	return speed;
}
