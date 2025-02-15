#pragma once
#include <SHADER.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Manager/ResourceManager.h"

class FrameBuffer 
{
public:
	FrameBuffer(const Shader& shader, int width, int height);
	~FrameBuffer();
	void BeginRender() const;
	void DoBloom();
	void DoBlur();
	void EndRender() const;
	void Render();
private:
	VAO vao;
	Shader shader;
	unsigned int fbo;
	unsigned int textureFbo;
	int width, height;

	void Init();
	void InitRenderData();
};