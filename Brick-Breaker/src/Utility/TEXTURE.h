#pragma once

#include <glad/glad.h>

class Texture
{
public:
	Texture();
	void LoadData(const char *filename, bool alpha);
	void LoadePng(const char *filename);
	void LoadImage(const char *filename);
	void Bind() const;
	void Unbind();
	void Delete() const;

private:
	GLuint ID;
	int width, height, nrChannels;
};

