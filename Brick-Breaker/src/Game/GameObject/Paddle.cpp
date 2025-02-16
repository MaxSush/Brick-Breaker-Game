#include "Paddle.h"
#include "Paddle.h"
#include "../Window/KeyListner.h"
#include <algorithm>
#include <Manager\ResourceManager.h>

Paddle::Paddle(const Texture& texture, glm::vec2 pos, glm::vec2 size)
	:
	GameObject(pos,size,texture),
	start_pos(pos),
	start_size(size)
{
}

Paddle::~Paddle()
{
}

void Paddle::Update(float dt,Rect& playzone, Ball* ball)
{
	glm::vec2 delta = velocity * speed * dt;
	rect.pos += delta;
	if (ball->IsStuck()) {
		ball->GetRect().pos = glm::vec2{ rect.size.x / 2.0f - ball->GetRadius(), -ball->GetRadius() * 2.0f} + rect.pos;
		ball->SetVelocity({0.0f,-1.0f});
	}

	DoWallCollision(playzone, ball);
}

void Paddle::DoBallCollision(Ball* ball)
{
	if (!cooldown) 
	{
		if (rect.CheckCollision(ball->GetRect())) 
		{
			float pad_center = rect.pos.x + (rect.size.x / 2.0f);
			float distance = (ball->GetRect().pos.x + ball->GetRadius()) - pad_center;
			float percentage = std::clamp(distance / (rect.size.x / 2.0f), -1.0f, 1.0f);
			
			glm::vec2 new_vel = { percentage,-1.0f };
			ball->SetVelocity(new_vel);
			cooldown = true;
			ResourceManager::PlayAudio("player", false);
		}
	}
}

void Paddle::Draw(SpriteRenderer* render)
{
	render->DrawSprite(texture, rect.pos, rect.size);
}

void Paddle::SetCooldown()
{
	cooldown = false;
}

void Paddle::Reset()
{
	velocity = { 0,0 };
	float speed = 550;
	bool cooldown = false;
	rect = Rect(start_pos, start_size);
}

Rect& Paddle::GetRect()
{
	return this->rect;
}

void Paddle::DoWallCollision(Rect& playzone, Ball* ball)
{
	if (KeyListner::IsKeyPressed(GLFW_KEY_LEFT))
	{
		velocity = { -1,0 };
	}
	else if (KeyListner::IsKeyPressed(GLFW_KEY_RIGHT))
	{
		velocity = { 1,0 };
	}
	else
	{
		velocity = { 0,0 };
	}

	// bound paddle and ball in playzone
	if (rect.pos.x <= playzone.Left)
	{
		rect.pos.x = playzone.Left;
		if (ball->IsStuck()) {
			ball->GetRect().pos.x = rect.pos.x + (rect.size.x / 2.0f - (ball->GetRect().size.x / 2.0f));
		}
	}
	else if (rect.pos.x + rect.size.x >= playzone.Right)
	{
		rect.pos.x = playzone.Right - rect.size.x;
		if (ball->IsStuck()) {
			ball->GetRect().pos.x = rect.pos.x + (rect.size.x / 2.0f - (ball->GetRect().size.x / 2.0f));
		}
	}
}
