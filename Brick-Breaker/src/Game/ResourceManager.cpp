#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

void ResourceManager::LoadTexture(const char* filename, bool alpha, std::string name)
{
	Textures[name] = LoadTextureFromFile(filename, alpha);
}

void ResourceManager::LoadShader(const char* VertexShaderFilename, const char* FragmentShaderFilename, std::string name)
{
	Shaders[name] = LoadShaderFromFile(VertexShaderFilename, FragmentShaderFilename);
}

const Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

const Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto& iter : Shaders)
    {
        iter.second.Delete();
    }
    for (auto& iter : Textures)
    {
        iter.second.Delete();
    }
}

Shader ResourceManager::LoadShaderFromFile(const char* VertexShaderFilename, const char* FragmentShaderFilename)
{
    Shader shader(VertexShaderFilename, FragmentShaderFilename);
    return shader;
}

Texture ResourceManager::LoadTextureFromFile(const char* filename, bool alpha)
{
    Texture texture;
    texture.LoadData(filename, alpha);
    texture.Unbind();

    return texture;
}
