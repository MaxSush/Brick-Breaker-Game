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

	void DrawCube(glm::vec2 pos, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
	void DrawSprite(const Texture& texture, glm::vec2 pos, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
private:
	Shader shader;
	VAO vao;
	void Init();
};