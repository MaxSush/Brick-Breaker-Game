#include "Ball.h"
#include "Ball.h"
#include "Ball.h"
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

void Ball::DoBrickColision(Collision& collision)
{
	Direction dir = std::get<1>(collision);
	glm::vec2 diff_vector = std::get<2>(collision);
	if (dir == LEFT || dir == RIGHT)		// horizontal collision
	{
		ReboundX();							// reverse
		float penetration = radius - std::abs(diff_vector.x);
		if (dir == LEFT)
			rect.pos.x += penetration;		// move right
		else
			rect.pos.x -= penetration;		// move left;
	}
	else
	{
		ReboundY();
		float penetration = radius - std::abs(diff_vector.y);
		if (dir == UP)
			rect.pos.y -= penetration;		// move up
		else
			rect.pos.y += penetration;		// move down
	}
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
	velocity.x = -glm::normalize(velocity).x;
}

void Ball::ReboundY()
{
	velocity.y = -glm::normalize(velocity).y;
}

Rect& Ball::GetRect()
{
	return rect;
}

glm::vec2& Ball::GetVelocity()
{
	return velocity;
}

void Ball::SetVelocity(glm::vec2& new_vel)
{
	velocity = new_vel;
}

float Ball::GetRadius() const
{
	return radius;
}

bool& Ball::IsStuck()
{
	return stuck;
}

void Ball::dowork()
{
}
