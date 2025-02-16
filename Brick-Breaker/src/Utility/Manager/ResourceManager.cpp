#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "sndfile.h"


std::unordered_map<std::string, Shader> ResourceManager::Shaders;
std::unordered_map<std::string, Texture> ResourceManager::Textures;
std::unordered_map<std::string, AudioInfo> ResourceManager::Audios;
std::queue<ALCuint> ResourceManager::sources_pool;

ALCdevice* ResourceManager::device;
ALCcontext* ResourceManager::context;

void ResourceManager::LoadTexture(const char* filename, bool alpha, std::string name)
{
	Textures[name] = LoadTextureFromFile(filename, alpha);
}

void ResourceManager::LoadShader(const char* VertexShaderFilename, const char* FragmentShaderFilename, std::string name)
{
	Shaders[name] = LoadShaderFromFile(VertexShaderFilename, FragmentShaderFilename);
}

void ResourceManager::LoadAudio(const char* filename, std::string name)
{
    Audios[name] = LoadAudioFromFile(filename);
}

const Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

const Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

static float volume = 0.0f;

const void ResourceManager::PlayAudio(std::string name, bool loop)
{
    AudioInfo& audio = Audios[name];
    alSourcei(audio.source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

    ALint state;
    alGetSourcei(audio.source, AL_SOURCE_STATE, &state);
    
    if (name == "win_bgm")
    {
        if (volume < 1.0f)
            volume += 0.1;
        alSourcef(audio.buffer, AL_GAIN, volume);
    }

    if (state != AL_PLAYING)
    {
        alSourcePlay(audio.source);
    }
    else if (state == AL_PLAYING && !(audio.duration > 2))
    {
        ALuint source;
        alGenSources(1, &source);
        alSourcef(source, AL_GAIN, 1.0f);
        alSourcef(source, AL_PITCH, 1.0f);
        alSourcei(source, AL_BUFFER, audio.buffer);
        alSourcePlay(source);
        sources_pool.push(source);
        while (true)
        {
            ALuint oldSource = sources_pool.front();
            ALint oldState;
            alGetSourcei(oldSource, AL_SOURCE_STATE, &oldState);
            // Only delete the source if it's stopped
            if (oldState != AL_PLAYING)
            {
                alDeleteSources(1, &oldSource);
                sources_pool.pop();
            }
            else
                break;
        }
    }
}

const void ResourceManager::PauseAudio(std::string name)
{
    AudioInfo& audio = Audios[name];
    ALint state;
    alGetSourcei(audio.source, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING)
    {
        alSourcePause(audio.source);
    }
}

const void ResourceManager::StopAudio(std::string name)
{
    AudioInfo& audio = Audios[name];
    ALint state;
    alGetSourcei(audio.source, AL_SOURCE_STATE, &state);
    
    volume = 0.0f;

    if (state == AL_PLAYING)
    {
        alSourceStop(audio.source);  // Stop the audio if it's playing
    }
}

void ResourceManager::Init()
{
	device = alcOpenDevice(nullptr);
	if (!device)
	{
		std::cerr << "Failed to open OpenAL device!" << std::endl;
		return;
	}
	context = alcCreateContext(device, nullptr);
	if (!context) {
		std::cerr << "Failed to create OpenAL context!" << std::endl;
		alcCloseDevice(device);
		return;
	}
	alcMakeContextCurrent(context);
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
    for (auto& iter : Audios)
    {
        iter.second.Delete();
    }
    alcDestroyContext(context);
    alcCloseDevice(device);
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

    return texture;
}

AudioInfo ResourceManager::LoadAudioFromFile(const char* filename)
{
    SF_INFO sfInfo;
    SNDFILE* file = sf_open(filename, SFM_READ, &sfInfo);
    if (!file)
    {
        std::cerr << "Failed to load audio file: " << filename << "\n";
    }

    if (!sf_format_check(&sfInfo)) {
        std::cerr << "Error: Invalid WAV format!" << std::endl;
    }

    std::vector<short> pcm(sfInfo.frames * sfInfo.channels);
    sf_count_t framesRead = sf_read_short(file, pcm.data(), pcm.size());
    if (framesRead < sfInfo.frames) {
        std::cerr << "Error to read all frames from the audio file." << std::endl;
    }
    sf_close(file);

    ALenum format = (sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    AudioInfo audio_info {};
    alGenBuffers(1, &audio_info.buffer);
    alBufferData(audio_info.buffer, format, pcm.data(), pcm.size() * sizeof(short), sfInfo.samplerate);

    alGenSources(1, &audio_info.source);

    alSourcei(audio_info.source, AL_BUFFER, audio_info.buffer);
    alSourcef(audio_info.source, AL_GAIN, 1.0f);
    alSourcef(audio_info.source, AL_PITCH, 1.0f);

    ALint size, frequency, channels, bits;
    alGetBufferi(audio_info.buffer, AL_SIZE, &size);
    alGetBufferi(audio_info.buffer, AL_FREQUENCY, &frequency);
    alGetBufferi(audio_info.buffer, AL_CHANNELS, &channels);
    alGetBufferi(audio_info.buffer, AL_BITS, &bits);

    float duration = static_cast<float>(size) / (frequency * channels * (bits / 8.0f));
    audio_info.duration = duration;

    return audio_info;
}
