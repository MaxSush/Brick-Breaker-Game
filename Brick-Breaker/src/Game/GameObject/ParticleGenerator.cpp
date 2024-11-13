#include "ParticleGenerator.h"
#include <random>

static float getRandomFloat(float min, float max) {
	std::random_device rd;  // Seed
	std::mt19937 gen(rd()); // Random number generator
	std::uniform_real_distribution<> distr(min, max); // Define range
	return distr(gen);
}

ParticleGenerator::ParticleGenerator(const Texture& texture, const Shader& shader)
	:
	shader(shader),
	texture(texture)
{
	p_render = new SpriteRenderer(shader);
}

ParticleGenerator::~ParticleGenerator()
{
	delete p_render;
}

void ParticleGenerator::Draw()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.Activate();
	shader.setFloat("brightnessFactor", brightnessFactor);

	// Get max vector range
	std::cout << particles.size() << "\n";

	for (auto& p : particles)
	{
		if (p.life > 0.0f)
		{
			p_render->DrawSprite(texture, p.pos, p.size, p.color);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::Update(float dt, Ball* ball)
{
		for (int i = 0; i < new_particle; ++i)
		{
			Spawn(ball);
		}

		for (size_t i = 0; i < particles.size(); ++i)
		{
			if (particles[i].life > 0)
			{
				Particle& p = particles[i];
				//p.pos += glm::normalize(p.velocity) * p.speed * dt;
				p.life -= dt * 3.0f;
				p.color.a -= dt * 3.0f;
			}
			else
			{
				particles.erase(particles.begin() + i);
			}
		}
}

void ParticleGenerator::Spawn(Ball* ball)
{
	Particle p = Particle();

	float offset = 0.5f;
	p.size = ball->GetSize() * offset;

	float p_random_x = getRandomFloat(0, p.size.x);
	float p_random_y = getRandomFloat(0, p.size.y);

	float x = getRandomFloat(0, 1);
	p.color = glm::vec4(x, x, x, 1.0f);
	p.pos = ball->GetPosition() + glm::vec2(p_random_x,p_random_y);

	particles.push_back(p);
}