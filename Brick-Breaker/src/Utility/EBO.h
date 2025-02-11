#pragma once
#include <glad/glad.h>

class EBO
{
public:
	EBO(GLuint* indices, GLsizeiptr size);
	void Bind() const;
	void Unbind();
	void Delete() const;
private:
	GLuint ID;
};

