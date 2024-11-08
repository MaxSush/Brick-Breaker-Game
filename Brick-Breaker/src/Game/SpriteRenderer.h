#pragma once

#include "Utility/SHADER.h"
#include "Utility/TEXTURE.h"

#include "Utility/VAO.h"
#include "Utility/VBO.h"
#include "Utility/EBO.h"

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader &shader);
	~SpriteRenderer();

	void DrawSprite(const Texture& texture, glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	VAO vao;
	void Init();
};