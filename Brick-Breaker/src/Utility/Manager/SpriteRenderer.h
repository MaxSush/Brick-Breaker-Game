#pragma once

#include "SHADER.h"
#include "TEXTURE.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader &shader);
	~SpriteRenderer();

	void DrawCube(glm::vec2 pos, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
	void DrawSprite(const Texture& texture, glm::vec2 pos, glm::vec2 size,  glm::vec4 color = glm::vec4(1.0f), float scale = 1);
private:
	Shader shader;
	VAO vao;
	void Init();
};