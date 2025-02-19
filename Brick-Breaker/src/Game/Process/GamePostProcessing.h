#pragma once
#include "SHADER.h"
#include "VAO.h"
#include "VBO.h"

class GameEffects
{
public:
	GameEffects(const Shader& shader, int width, int height);
	~GameEffects();
	void BeginRender() const;
	void EndRender() const;
	void Render(float dt);
	void Reset();

	bool chaos = false, confuse = false, shake = false;

private:
	GLuint MSFBO, FBO;
	GLuint RBO;
	GLuint textureId;
	int width, height;

	Shader shader;
	VAO vao;

	void Init();
	void InitRenderData();

};