#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const Shader& shader)
	:
	shader(shader)
{
	Init();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawSprite(const Texture& texture, glm::vec2 pos, glm::vec2 size, glm::vec3 color)
{
	shader.Activate();

	glm::mat4 projection = glm::ortho(0.0f, 900.0f, 700.0f, 0.0f, -1.0f, 1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.setMat4("projection", projection);
	shader.setMat4("model", model);
	shader.setVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void SpriteRenderer::Init()
{
	float vertices[] = {
		1.0f, 0.0f, 1.0f, 0.0f,		// top right
		1.0f, 1.0f, 1.0f, 1.0f,		// bottom right
		0.0f, 1.0f, 0.0f, 1.0f,		// bottom left
		0.0f, 0.0f, 0.0f, 0.0f		// top left
	};

	unsigned int indices[] = {
		0, 1, 3,	// first triangle
		1, 2, 3		// second triangle
	};
	
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	vao.Unbind();
}
