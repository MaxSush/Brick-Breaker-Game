#pragma once

#include <vector>

#include "Utility/Texture.h"
#include "Utility/Shader.h"
#include "Ball.h"

struct Particle
{
	glm::vec2 pos = glm::vec2(0.0f);
	glm::vec2 size = glm::vec2(10.0f);
	glm::vec4 color = glm::vec4(0.0f);

	float life = 1.0f;
};

class ParticleGenerator
{
public:
	ParticleGenerator(const Texture& texture, const Shader& shader);
	~ParticleGenerator();
	void Draw();
	void Update(float dt, Ball* ball);
private:
	Texture texture;
	Shader shader;
	SpriteRenderer* p_render = nullptr;
	std::vector<Particle> particles;

	int new_particle = 5;
	float brightnessFactor = 2;

	void Spawn(Ball* ball);
};