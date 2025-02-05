#pragma once 

#include <unordered_map>
#include <queue>

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include "Utility/SHADER.h"
#include "Utility/TEXTURE.h"

struct AudioInfo {
    ALuint buffer;
    ALuint source;
    void Delete() {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    }
};

class ResourceManager
{
public:
    static void LoadTexture(const char* filename, bool alpha, std::string name);
    static void LoadShader(const char* VertexShaderFilename, const char* FragmentShaderFilename, std::string name);
    static void LoadAudio(const char* filename, std::string name);

    static const Shader GetShader(std::string name);
    static const Texture GetTexture(std::string name);
    static const void PlayAudio(std::string name, bool loop);

    static void Init();
    static void Clear();

private:
    static std::unordered_map<std::string, Shader> Shaders;
    static std::unordered_map<std::string, Texture> Textures;
    static std::unordered_map<std::string, AudioInfo> Audios;

    static constexpr int MAX_SOURCES = 4;
    static std::queue<ALCuint> sources_pool;

    static ALCdevice* device;
    static ALCcontext* context;
    static Shader LoadShaderFromFile(const char* VertexShaderFilename, const char* FragmentShaderFilename);
    static Texture LoadTextureFromFile(const char* filename, bool alpha);
    static AudioInfo LoadAudioFromFile(const char* filename);
};