#include "Ball.h"


Ball::Ball(glm::vec2 pos, float radius, const Texture& texture)
	:
	GameObject(pos, glm::vec2(radius * 2), texture),
	radius(radius)
{
}

void Ball::Draw(SpriteRenderer* render)
{
	render->DrawSprite(texture, rect.pos, rect.size);
}

void Ball::Update(float dt)
{
	if (!stuck)
	{
		rect.pos += glm::normalize(velocity) * speed * dt;
	}
}

bool Ball::DoWallCollision(Rect& playzone)
{
	bool collided = false;
	if (!stuck)
	{
		if (rect.pos.x < playzone.Left)
		{
			ReboundX();
			rect.pos.x = playzone.Left;
			collided = true;
		}
		else if ((rect.pos.x + rect.size.x) > playzone.Right)
		{
			ReboundX();
			rect.pos.x = playzone.Right - rect.size.x;
			collided = true;
		}

		if (rect.pos.y < playzone.Top)
		{
			ReboundY();
			collided = true;
		}
		else if ((rect.pos.y + rect.size.y) > playzone.Bottom)
		{
			ReboundY();
			rect.pos.y = playzone.Bottom - rect.size.y;
			collided = true;
		}
	}
	return collided;
}

void Ball::SetBall()
{
	if (KeyListner::isKeyPressed(GLFW_KEY_SPACE))
	{
		stuck = false;
	}
}

void Ball::ReboundX()
{
	velocity.x = -velocity.x;
}

void Ball::ReboundY()
{
	velocity.y = -velocity.y;
}

Rect& Ball::GetRect()
{
	return rect;
}

glm::vec2& Ball::GetVelocity()
{
	return velocity;
}

float Ball::GetRadius() const
{
	return radius;
}

bool& Ball::IsStuck()
{
	return stuck;
}
