#pragma once
#include <glad/glad.h>

class VBO
{
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind() const;
	void Unbind();
	void Delete() const;
private:
	GLuint ID;
};

