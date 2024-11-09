#pragma once

#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader() = default;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate() const;

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec4(const std::string& name, glm::vec4 value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;

	void Delete() const;
private:
	void compileErrors(unsigned int shader, const char* type);
};

