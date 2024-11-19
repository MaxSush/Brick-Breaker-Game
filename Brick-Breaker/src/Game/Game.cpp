#include "Game.h"
#include "Game.h"

#include "../Window/glfw_window.h"
#include <iostream>

namespace Breaker
{
	Game::Game(const WinProps* props)
		:
		props(props),
		playzone(Rect(glm::vec2(0, 0), glm::vec2(props->width, props->height)))
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

		ResourceManager::LoadShader("assets/cubeShader.vs", "assets/cubeShader.fg", "cube");
		ResourceManager::LoadShader("assets/particle.vs", "assets/particle.fg", "particle");

		sprite = new SpriteRenderer(ResourceManager::GetShader("cube"));
		p_generator = new ParticleGenerator(ResourceManager::GetTexture("particle"), ResourceManager::GetShader("particle"));

		glm::vec2 paddle_size = { 135.0f,20.0f };
		glm::vec2 paddle_pos = { (props->width / 2.0f) - (paddle_size.x / 2.0f),props->height - (paddle_size.y * 2.0f)  - 100 };
		paddle = new Paddle(ResourceManager::GetTexture("paddle"), paddle_pos, paddle_size);

		float ball_radius = 10.0f;
		glm::vec2 ball_pos = glm::vec2{ paddle_size.x / 2.0f - ball_radius, -ball_radius * 2.0f } + paddle_pos;
		ball = new Ball(ball_pos, ball_radius, ResourceManager::GetTexture("ball"));

		level = new GameLevel();
		level->LoadLevel("assets/1level.lvl", static_cast<int>(props->width), static_cast<int>(props->height / 4.0f));
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
			sprite->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(900.0f, 700.0f));
			level->Draw(sprite);
			paddle->Draw(sprite);
			ball->Draw(sprite);

			if (!ball->IsStuck())
			{
				p_generator->Draw();
			}
		}
	}

	void Breaker::Game::DoCollision()
	{
		bool collisionHappened = false;
		float curColDist = 0.0;
		int curColIndex = 0;
		Collision collision;

		for (size_t i = 0; i < bricks->size(); i++)
		{
			auto& b = (*bricks)[i];
			Rect b_rect = b.GetRect();
			Collision col = b_rect.CheckCollision(ball->GetRect(), ball->GetRadius());
			if (!b.IsDestroyed())
			{
				if (std::get<0>(col))
				{
					const float newColDist = glm::length(ball->GetRect().GetCenter() - b.GetRect().GetCenter());
					if (collisionHappened)
					{
						if (newColDist < curColDist)
						{
							curColDist = newColDist;
							curColIndex = i;
							collision = col;
						}
					}
					else
					{
						curColDist = newColDist;
						curColIndex = i;
						collision = col;
						collisionHappened = true;
					}
				}
			}
		}
		if (collisionHappened)
		{
			auto& b = (*bricks)[curColIndex];
			if (!b.IsSolid())
				b.SetIsDestroyed(true);
			paddle->SetCooldown();
			ball->DoBrickColision(collision);
		}
	}
}