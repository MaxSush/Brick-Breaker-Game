#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, const Texture& texture)
	:
	rect(Rect(pos,size)),
	texture(texture)
{
}
