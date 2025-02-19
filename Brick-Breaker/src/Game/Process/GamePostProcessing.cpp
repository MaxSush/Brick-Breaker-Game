#include "GamePostProcessing.h"

GameEffects::GameEffects(const Shader& shader, int width, int height)
	:
	shader(shader),
	width(width), height(height)
{
	Init();
}

GameEffects::~GameEffects()
{
	glDeleteFramebuffers(1, &FBO);
	glDeleteFramebuffers(1, &MSFBO);
	glDeleteRenderbuffers(1, &RBO);
	shader.Delete();
	glDeleteTextures(1, &textureId);
}

void GameEffects::BeginRender() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GameEffects::EndRender() const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->MSFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GameEffects::Render(float dt)
{
	shader.Activate();
	shader.setFloat("time", dt);
	shader.setInt("confuse", this->confuse);
	shader.setInt("chaos", this->chaos);
	shader.setInt("shake", this->shake);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.Unbind();
}

void GameEffects::Reset()
{
	shader.setBool("confuse", false);
	shader.setBool("chaos", false);
	shader.setBool("shake", false);
	chaos = false;
	confuse = false;
	shake = false;
}

void GameEffects::Init()
{
	// Multisample Framebuffer
	glGenFramebuffers(1, &MSFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);

	glNamedRenderbufferStorageMultisample(RBO, 4, GL_RGB, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;
	
	// Texture FrameBuffer
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;
	
	InitRenderData();
	//glUniform1i(glGetUniformLocation(shader.ID, "annoy"), 0);

	float offset = 1.0f / 300.0f;
	float offsets[9][2] = {
		{ -offset,  offset  },  // top-left
		{  0.0f,    offset  },  // top-center
		{  offset,  offset  },  // top-right
		{ -offset,  0.0f    },  // center-left
		{  0.0f,    0.0f    },  // center-center
		{  offset,  0.0f    },  // center - right
		{ -offset, -offset  },  // bottom-left
		{  0.0f,   -offset  },  // bottom-center
		{  offset, -offset  }   // bottom-right    
	};
	int edge_kernel[9] = {
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};
	float blur_kernel[9] = {
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
	};
	shader.Activate();

	glUniform2fv(glGetUniformLocation(shader.ID, "offsets"), 9, (float*)offsets);	// note
	glUniform1iv(glGetUniformLocation(shader.ID, "edge_kernel"), 9, edge_kernel);
	glUniform1fv(glGetUniformLocation(shader.ID, "blur_kernel"), 9, blur_kernel);

}

void GameEffects::InitRenderData()
{
	float vertices[] = {
		// positions // texCoords
		-1.0f,  1.0f,	 0.0f, 1.0f,
		-1.0f, -1.0f,	 0.0f, 0.0f,
		 1.0f, -1.0f,	 1.0f, 0.0f,
		-1.0f,  1.0f,	 0.0f, 1.0f,
		 1.0f, -1.0f,	 1.0f, 0.0f,
		 1.0f,  1.0f,	 1.0f, 1.0f
	};
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	vao.LinkAttrib(vbo, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vbo.Unbind();
	vao.Unbind();
}
