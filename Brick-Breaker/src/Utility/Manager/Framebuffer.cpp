#include "Framebuffer.h"

FrameBuffer::FrameBuffer(const Shader& shader, Rect rect)
	:
	shader(shader),
	rect(rect)
{
	Init();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteTextures(1, &textureFbo);

	glDeleteFramebuffers(1, &fbo);


	shader.Delete();
}

void FrameBuffer::BeginRender() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void FrameBuffer::EndRender() const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Default framebuffer
	//glBlitFramebuffer(rect.Left, rect.Top, rect.Right, rect.Bottom, rect.Left, rect.Top, rect.Right, rect.Bottom, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	
	shader.Activate();

	shader.setFloat("blurStrength", 1.5f);
	shader.setFloat("brightness", 0.5f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureFbo);
	shader.setInt("image", 0);
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.Unbind();
}

GLuint GenTexture(int width, int height)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// adjust width and height
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return textureId;
}

void FrameBuffer::Init()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	textureFbo = GenTexture(rect.Right, rect.Bottom);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureFbo, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	InitRenderData();
}

void FrameBuffer::InitRenderData()
{
	float vertices[] = {
		// pos        // tex
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};

	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	vbo.Unbind();
	vao.Unbind();
}
