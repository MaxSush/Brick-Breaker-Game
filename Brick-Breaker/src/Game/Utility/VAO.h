#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	VAO();
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
	void Bind() const;
	void Unbind();
	void Delete() const;
private:
	GLuint ID;
};

