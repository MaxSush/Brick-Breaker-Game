#include "Brick.h"
#include "Brick.h"

Brick::Brick(const Texture& texture, glm::vec2 pos, glm::vec2 size)
	:
	GameObject(pos,size,texture)
{
}

Brick::~Brick()
{
}

void Brick::Draw(SpriteRenderer* render)
{
	render->DrawSprite(texture, rect.pos, rect.size, color);
}

void Brick::SetColor(glm::vec4 c)
{
	color = c;
}

void Brick::SetSolid()
{
	is_solid = true;
}

bool Brick::IsSolid() const
{
	return is_solid;
}

bool Brick::IsDestroyed() const
{
	return is_destroyed;
}

void Brick::SetIsDestroyed(bool val)
{
	is_destroyed = val;
}

Rect& Brick::GetRect()
{
	return rect;
}
