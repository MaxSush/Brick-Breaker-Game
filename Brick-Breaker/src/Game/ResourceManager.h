#pragma once 

#include <map>

#include "Utility/SHADER.h"
#include "Utility/TEXTURE.h"

class ResourceManager
{
public:
    static void LoadTexture(const char* filename, bool alpha, std::string name);
    static void LoadShader(const char* VertexShaderFilename, const char* FragmentShaderFilename, std::string name);
    static const Shader GetShader(std::string name);
    static const Texture GetTexture(std::string name);

    static void Clear();

private:
    ResourceManager() {}

    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture> Textures;

    static Shader LoadShaderFromFile(const char* VertexShaderFilename, const char* FragmentShaderFilename);
    static Texture LoadTextureFromFile(const char* filename, bool alpha);
};