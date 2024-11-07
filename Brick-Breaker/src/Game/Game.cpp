#include "Game.h"

#include <iostream>

Breaker::Game::Game()
{
}

Breaker::Game::~Game()
{
	ResourceManager::Clear();
}

void Breaker::Game::Init()
{
	ResourceManager::LoadShader("assets/cubeShader.vs", "assets/cubeShader.fg", "cube");

	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};
	

	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.Unbind();
}

void Breaker::Game::Update(float dt)
{
}

void Breaker::Game::Render()
{
	ResourceManager::GetShader("cube").Activate();
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
