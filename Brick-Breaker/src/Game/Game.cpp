#include "Game.h"

#include "../Window/glfw_window.h"
#include <iostream>

namespace Breaker
{
	Game::Game(const WinProps* props)
		:
		props(props)
	{
		playzone = { 0,0,(float)props->width, (float)props->height };
	}

	Game::~Game()
	{
		ResourceManager::Clear();
		delete sprite;
		delete ball;
	}

	void Game::Init()
	{
		ResourceManager::LoadTexture("assets/background.jpg", false, "background");
		ResourceManager::LoadTexture("assets/ball.png", true, "ball");

		ResourceManager::LoadShader("assets/cubeShader.vs", "assets/cubeShader.fg", "cube");

		sprite = new SpriteRenderer(ResourceManager::GetShader("cube"));

		ball = new Ball(props->window, glm::vec2(props->width / 2.0f, props->height - 100.0f), 10.0f, ResourceManager::GetTexture("ball"));
	}

	void Game::Update(float dt)
	{
		ball->SetBall();
		ball->Update(dt);
		ball->DoWallCollision(playzone);
	}

	void Game::Render()
	{
		if (state == GameState::GAME_ACTIVE)
		{
			sprite->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(900.0f, 700.0f));
			ball->Draw(*sprite);
		}
	}
}