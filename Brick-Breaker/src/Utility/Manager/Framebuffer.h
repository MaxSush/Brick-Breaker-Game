#pragma once
#include <SHADER.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Manager/ResourceManager.h"
#include "Rect.h"

class FrameBuffer 
{
public:
	FrameBuffer(const Shader& shader, Rect rect);
	~FrameBuffer();
	void BeginRender() const;
	void EndRender() const;
	void Render();
private:
	VAO vao;
	Shader shader;
	unsigned int fbo;
	unsigned int textureFbo;
	Rect rect;

	void Init();
	void InitRenderData();
};