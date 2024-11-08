#include "GameObject.h"

GameObject::GameObject(GLFWwindow* window, glm::vec2 pos, glm::vec2 size, const Texture& texture)
	:
	window(window),
	pos(pos),
	size(size),
	texture(texture)
{
}

GameObject::~GameObject()
{
}
