#include "../Window/glfw_window.h"
#include "Game.h"
#include "Game.h"
#include <iostream>

namespace Breaker
{
	Game::Game(const WinProps* props)
		:
		props(props),
		playzone(Rect(offset, offset, 900 - offset, 700 - offset))
	{
	}

	Game::~Game()
	{
		ResourceManager::Clear();
		delete effects;
		delete level;
		delete paddle;
		delete p_generator;
		delete ball;
		delete sprite;
	}

	void Game::Init()
	{
		ResourceManager::Init();
		ResourceManager::LoadTexture("assets/background.jpg", false, "background");
		ResourceManager::LoadTexture("assets/ball.png", true, "ball");
		ResourceManager::LoadTexture("assets/particle.png", true, "particle");
		ResourceManager::LoadTexture("assets/paddle.png", true, "paddle");
		ResourceManager::LoadTexture("assets/brick.png", true, "brick");
		ResourceManager::LoadTexture("assets/solid.png", false, "solid");
		ResourceManager::LoadTexture("assets/bevel.png", true, "bevel");

		ResourceManager::LoadTexture("assets/powerup_passthrough.png", true, "passthrough");
		ResourceManager::LoadTexture("assets/powerup_chaos.png", true, "chaos");
		ResourceManager::LoadTexture("assets/powerup_confuse.png", true, "confuse");
		ResourceManager::LoadTexture("assets/powerup_increase.png", true, "increase");
		ResourceManager::LoadTexture("assets/powerup_speed.png", true, "speed");
		ResourceManager::LoadTexture("assets/powerup_sticky.png", true, "sticky");

		ResourceManager::LoadShader("assets/cubeShader.vs", "assets/cubeShader.fg", "sprite");
		ResourceManager::LoadShader("assets/particle.vs", "assets/particle.fg", "particle");
		ResourceManager::LoadShader("assets/postProcessing.vs", "assets/postProcessing.fg", "postprocessor");

		ResourceManager::LoadAudio("assets/breakout.mp3", "breakout");
		ResourceManager::LoadAudio("assets/bleep.mp3", "brick");
		ResourceManager::LoadAudio("assets/bleep.mp3", "wall");
		ResourceManager::LoadAudio("assets/bleep.wav", "player");
		ResourceManager::LoadAudio("assets/powerup.wav", "powerup");
		ResourceManager::LoadAudio("assets/solid.wav", "solid");


		sprite = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		p_generator = new ParticleGenerator(ResourceManager::GetTexture("particle"), ResourceManager::GetShader("particle"));

		glm::vec2 paddle_size = { 135.0f,20.0f };
		glm::vec2 paddle_pos = { (playzone.Right / 2.0f) - (paddle_size.x / 2.0f),playzone.Bottom - (paddle_size.y * 2.0f) };
		paddle = new Paddle(ResourceManager::GetTexture("paddle"), paddle_pos, paddle_size);

		float ball_radius = 10.0f;
		glm::vec2 ball_pos = glm::vec2{ paddle_size.x / 2.0f - ball_radius, -ball_radius * 2.0f } + paddle_pos;
		ball = new Ball(ball_pos, ball_radius, ResourceManager::GetTexture("ball"));

		effects = new GameEffects(ResourceManager::GetShader("postprocessor"), props->width, props->height);
	}

	void Game::LoadLevel(int lvl)
	{
		if (level)
		{
			bricks->clear();
			delete level;
			level = nullptr;
		}
		level = new GameLevel();
		level->LoadLevel(lvl, playzone);
		bricks = level->GetBricks();
	}

	void Game::Update(float dt)
	{
		paddle->Update(dt, playzone, ball);
		ball->SetBall();
		powerups.UpdatePowerUps(dt, playzone, ball, effects);
		if (shakeTime > 0.0f) {
			shakeTime -= dt;
			if (shakeTime <= 0.0f) {
				effects->shake = false;
			}
		}
		if (!ball->IsStuck())
		{
			FixBallBrickCollision();
			ball->Update(dt);
			paddle->DoBallCollision(ball);
			PowerUps::PowerBlock* block = powerups.CheckCollision(paddle->GetRect());
			if (block != nullptr) {
				ResourceManager::PlayAudio("powerup", false);
				ActivatePowerUps(block);
			}
			if (ball->DoWallCollision(playzone))
			{
				ResourceManager::PlayAudio("wall", false);
				paddle->SetCooldown();
			}
			p_generator->Update(dt, ball);
		}
		else
		{
			p_generator->ClearParticles();
		}
		ResourceManager::PlayAudio("breakout", true);
	}

	void Game::Render()
	{
		if (state == GameState::GAME_ACTIVE)
		{
			effects->BeginRender();
			sprite->DrawSprite(ResourceManager::GetTexture("background"), { 0,0 }, { 900,700 });
			level->Draw(sprite);
			powerups.DrawPowerUps(sprite);
			paddle->Draw(sprite);
			ball->Draw(sprite);

			if (!ball->IsStuck())
			{
				p_generator->Draw();
			}
			effects->EndRender();
			effects->Render(float(glfwGetTime()));
			sprite->DrawSprite(ResourceManager::GetTexture("bevel"), { 0,0 }, { props->width, props->height }, { 0.0f, 0.8f, 0.8f, 1.0f });
		}
	}

	// fix for multiple collision at single touch
	void Breaker::Game::FixBallBrickCollision()
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
			paddle->SetCooldown();
			if (!ball->pass_through || !b.IsSolid()) {
				ball->DoBrickColision(collision);
				if (!b.IsSolid()) {
					ResourceManager::PlayAudio("brick", false);
					b.SetIsDestroyed(true);
					powerups.SpawnPowerUps(b.GetRect());
				}
			}
			if (!ball->pass_through && b.IsSolid()) {
				ResourceManager::PlayAudio("solid", false);
				shakeTime = 0.10f;
				effects->shake = true;
			}
		}
	}

	void Game::ActivatePowerUps(PowerUps::PowerBlock* block)
	{
		if (block->type == PowerType::SPEED)
		{
			ball->SetSpeed(1.2f);
		}
		else if (block->type == PowerType::STICKY)
		{
			ball->stuck = true;
		}
		else if (block->type == PowerType::PAD_SIZE_INCREASE)
		{
			paddle->GetRect().size.x += 50;
			paddle->GetRect().size.y += 1;
		}
		else if (block->type == PowerType::PASS_THROUGH)
		{
			ball->pass_through = true;
		}
		else if (block->type == PowerType::CHAOS)
		{
			if (!effects->confuse)
			{
				effects->chaos = true;
			}
		}
		else if (block->type == PowerType::CONFUSE)
		{
			if (!effects->chaos)
			{
				effects->confuse = true;
			}
		}
	}
}
