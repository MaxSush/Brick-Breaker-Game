#include "Game.h"
#include "Game.h"
#include "Game.h"

#include "../Window/glfw_window.h"
#include <iostream>

namespace Breaker
{
	Game::Game(const WinProps* props)
		:
		props(props),
		playzone(Rect(offset,offset,900 - offset,700 - offset))
	{
	}

	Game::~Game()
	{
		ResourceManager::Clear();
		delete sprite;
		delete ball;
		delete p_generator;
		delete paddle;
		delete level;
	}

	void Game::Init()
	{
		ResourceManager::LoadTexture("assets/background.jpg", false, "background");
		ResourceManager::LoadTexture("assets/ball.png", true, "ball");
		ResourceManager::LoadTexture("assets/particle.png", true, "particle");
		ResourceManager::LoadTexture("assets/paddle.png", true, "paddle");
		ResourceManager::LoadTexture("assets/brick.png", true, "brick");
		ResourceManager::LoadTexture("assets/solid.png", true, "solid");

		ResourceManager::LoadShader("assets/cubeShader.vs", "assets/cubeShader.fg", "sprite");
		ResourceManager::LoadShader("assets/particle.vs", "assets/particle.fg", "particle");

		sprite = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		p_generator = new ParticleGenerator(ResourceManager::GetTexture("particle"), ResourceManager::GetShader("particle"));

		glm::vec2 paddle_size = { 135.0f,20.0f };
		glm::vec2 paddle_pos = { (playzone.Right / 2.0f) - (paddle_size.x / 2.0f),playzone.Bottom - (paddle_size.y * 2.0f) };
		paddle = new Paddle(ResourceManager::GetTexture("paddle"), paddle_pos, paddle_size);

		float ball_radius = 10.0f;
		glm::vec2 ball_pos = glm::vec2{ paddle_size.x / 2.0f - ball_radius, -ball_radius * 2.0f } + paddle_pos;
		ball = new Ball(ball_pos, ball_radius, ResourceManager::GetTexture("ball"));

		level = new GameLevel();
		level->LoadLevel("assets/1level.lvl", playzone);
		bricks = level->GetBricks();
	}

	void Game::Update(float dt)
	{
		paddle->Update(dt, playzone, ball);
		ball->SetBall();

		if (!ball->IsStuck())
		{
			DoCollision();
			ball->Update(dt);

			paddle->DoBallCollision(ball);

			if (ball->DoWallCollision(playzone))
			{
				paddle->SetCooldown();
			}
			p_generator->Update(dt, ball);
		}
	}

	void Game::Render()
	{

		if (state == GameState::GAME_ACTIVE)
		{
			sprite->DrawSprite(ResourceManager::GetTexture("background"), playzone.pos, playzone.size);
			level->Draw(sprite);
			paddle->Draw(sprite);
			ball->Draw(sprite);

			if (!ball->IsStuck())
			{
				p_generator->Draw();
			}
		}
	}

	// fix for multiple collision at single touch
	void Breaker::Game::DoCollision()
	{
		bool collisionHappened = false;
		float curColDist = std::numeric_limits<float>::max();
		int curColIndex = -1;
		Collision collision;

		for (int i = 0; i < bricks->size(); i++)
		{
			auto& b = (*bricks)[i];
			if (b.IsDestroyed())
				continue; // Skip destroyed bricks

			Rect b_rect = b.GetRect();
			Collision col = b_rect.CheckCollision(ball->GetRect(), ball->GetRadius());

			if (std::get<0>(col)) 
			{ // Collision occurred
				float newColDist = glm::length(ball->GetRect().GetCenter() - b_rect.GetCenter());
				if (newColDist < curColDist) 
				{
					curColDist = newColDist;
					curColIndex = i;
					collision = col;
					collisionHappened = true;
				}
			}
		}
		if (collisionHappened && curColIndex != -1) 
		{
			auto& b = (*bricks)[curColIndex];
			if (!b.IsSolid())
				b.SetIsDestroyed(true);

			paddle->SetCooldown();
			ball->DoBrickColision(collision);
		}
	}
	void Breaker::Game::DrawBeveler()
	{

	}
}