#pragma once
#include "Utility/SHADER.h"
#include "Utility/VAO.h"
#include "Utility/VBO.h"

class GameEffects
{
public:
	GameEffects(const Shader& shader, int width, int height);
	~GameEffects();
	void BeginRender() const;
	void EndRender() const;
	void Render(float dt);

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