#pragma once

#include "Manager/SpriteRenderer.h"
#include "Utility/Rect.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject() = default;
	GameObject(glm::vec2 pos, glm::vec2 size, const Texture& texture);
	~GameObject() { }
	virtual void Draw(SpriteRenderer* render) = 0;
protected:
	Rect rect;
	Texture texture;
};