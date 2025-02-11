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

void SpriteRenderer::DrawCube(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{
	shader.Activate();
	glm::mat4 projection = glm::ortho(0.0f, 900.0f, 700.0f, 0.0f, -1.0f, 1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.setMat4("projection", projection);
	shader.setMat4("model", model);
	shader.setVec4("spriteColor", color);
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void SpriteRenderer::DrawSprite(const Texture& texture, glm::vec2 pos, glm::vec2 size, glm::vec4 color, float scale)
{
	shader.Activate();

	glm::mat4 projection = glm::ortho(0.0f, 900.0f, 700.0f, 0.0f, -1.0f, 1.0f);

	float center_x = pos.x + (size.x / 2.0f);
	float center_y = pos.y + (size.y / 2.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos , 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	model = model *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, 0.0f));

	shader.setMat4("projection", projection);
	shader.setMat4("model", model);
	shader.setVec4("spriteColor", color);

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
