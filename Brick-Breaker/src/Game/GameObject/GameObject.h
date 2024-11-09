#pragma once

#include "SpriteRenderer.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject(GLFWwindow* window, glm::vec2 pos, glm::vec2 size, const Texture& texture);
	~GameObject() { }
	virtual void Draw(SpriteRenderer& render) = 0;
protected:
	glm::vec2 pos, size;
	GLFWwindow* window = nullptr;
	Texture texture;
};