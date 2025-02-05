#pragma once 

#include "Utility/Rect.h"
#include "GameObject/GameObject.h"

class Brick : public GameObject
{
public:
	Brick() = default;
	Brick(const Texture& texture, glm::vec2 pos, glm::vec2 size);
	~Brick();
	void Draw(SpriteRenderer* render) override;

	void SetColor(glm::vec4 c);
	void SetSolid();
	bool IsSolid() const;
	bool IsDestroyed() const;
	void SetIsDestroyed(bool val);

	Rect& GetRect();
private:
	glm::vec4 color = { 1,1,1,1 };
	bool is_solid = false;
	bool is_destroyed = false;
};