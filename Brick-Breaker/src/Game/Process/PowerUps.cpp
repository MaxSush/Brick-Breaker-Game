#include "PowerUps.h"
#include <random>


static bool ShouldSpawn(unsigned int  chance)
{
	std::uniform_int_distribution<unsigned int > dist(0, chance - 1);
	return dist(Rect::rng) == 0;
}

PowerUps::PowerUps()
{
}

void PowerUps::SpawnPowerUps(Rect& brickBlock)
{
	if (ShouldSpawn(30))	// SPEED
	{
		powerups.push_back(PowerBlock(brickBlock.pos, brickBlock.size, ResourceManager::GetTexture("speed"), PowerType::SPEED, 0.0f));
		//std::cout << "Spawned SPEED Poweerup" << "\n";
		return;
	}
	if (ShouldSpawn(25))	// PAD_SIZE_INCREASE
	{
		powerups.push_back(PowerBlock(brickBlock.pos, brickBlock.size, ResourceManager::GetTexture("increase"), PowerType::PAD_SIZE_INCREASE, 0.0f));
		//std::cout << "Spawned PAD_SIZE_INCREASE Poweerup" << "\n";
		return;
	}
	if (ShouldSpawn(20))	// PASS_THROUGH
	{
		powerups.push_back(PowerBlock(brickBlock.pos, brickBlock.size, ResourceManager::GetTexture("passthrough"), PowerType::PASS_THROUGH, 10.0f));
		//std::cout << "Spawned PASS_THROUGH Poweerup" << "\n";
		return;
	}
	if (ShouldSpawn(30)) // STICKY
	{
		powerups.push_back(PowerBlock(brickBlock.pos, brickBlock.size, ResourceManager::GetTexture("sticky"), PowerType::STICKY, 3.0f));
		//std::cout << "Spawned STICKY Poweerup" << "\n";
		return;
	}
	if (ShouldSpawn(25))	// CONFUSE
	{
		powerups.push_back(PowerBlock(brickBlock.pos, brickBlock.size, ResourceManager::GetTexture("confuse"), PowerType::CONFUSE, 5.0f));
		//std::cout << "Spawned CONFUSE Poweerup" << "\n";
		return;
	}
	if (ShouldSpawn(20))	// CHAOS
	{
		powerups.push_back(PowerBlock(brickBlock.pos, brickBlock.size, ResourceManager::GetTexture("chaos"), PowerType::CHAOS, 5.0f));
		//std::cout << "Spawned CHAOS Poweerup" << "\n";
		return;
	}
}

void PowerUps::UpdatePowerUps(float dt, Rect& playzone, Ball* ball, GameEffects* effects)
{
	for (auto& block : powerups)
	{
		if (!block.destroyed)
		{
			block.UpdatePowerBlock(dt, playzone);
		}
		if (block.activated)
		{
			block.duration -= dt;
			if (block.duration <= 0.0f)
			{
				block.activated = false;
				if (block.type == PowerType::STICKY)
				{
					if (!IsOtherPowerUpsActivated(PowerType::STICKY))
					{
						//std::cout << "sticky Deactivated" << block.duration << "\n";
						ball->stuck = false;
					}
				}
				else if (block.type == PowerType::PASS_THROUGH)
				{
					if (!IsOtherPowerUpsActivated(PowerType::PASS_THROUGH))
					{
						ball->pass_through = false;
						//std::cout << "pass through Deactivated" << block.duration << "\n";
					}
				}
				else if (block.type == PowerType::CHAOS)
				{
					if (!IsOtherPowerUpsActivated(PowerType::CHAOS))
					{
						effects->chaos = false;
						//std::cout << "Chaos Deactivated" << block.duration << "\n";
					}
				}
				else if (block.type == PowerType::CONFUSE)
				{
					if (!IsOtherPowerUpsActivated(PowerType::CONFUSE))
					{
						effects->confuse = false;
						//std::cout << "Confuse Deactivated" << block.duration << "\n";
					}
				}
			}
		}
	}
	powerups.erase(std::remove_if(powerups.begin(), powerups.end(), [](PowerBlock& block) {
		if (!block.activated && block.destroyed) {
			//std::cout << "Removing PowerBlock of type: " << static_cast<int>(block.type) << "\n";
			return true;
		}
		return false;
		}), powerups.end());

}

PowerUps::PowerBlock* PowerUps::CheckCollision(Rect& paddleRect)
{
	for (auto& block : powerups)
	{
		if (!block.destroyed)
		{
			if (block.CheckCollision(paddleRect))
			{
				block.DestroyPowerBlock();
				block.activated = true;
				return &block;
			}
		}
	}
	return nullptr;
}

void PowerUps::DrawPowerUps(SpriteRenderer* render)
{
	for (auto& block : powerups)
	{
		if (!block.destroyed)
			block.Draw(render);
	}
}

bool PowerUps::IsOtherPowerUpsActivated(PowerType type)
{
	for (auto& block : powerups)
	{
		if (block.activated)
		{
			if (block.type == type)
				return true;
		}
	}
	return false;
}

void PowerUps::Reset()
{
	for (auto& p : powerups)
	{
		p.destroyed = true;
		p.activated = false;
		p.DestroyPowerBlock();
	}
}

PowerUps::PowerBlock::PowerBlock(glm::vec2 pos, glm::vec2 size, const Texture& texture, PowerType type, float duration)
	:
	GameObject(pos,size,texture),
	type(type),
	duration(duration)
{
}

void PowerUps::PowerBlock::DestroyPowerBlock()
{
	this->destroyed = true;
	//std::cout << "Destroyed" << static_cast<int>(type) << "Poweerup" << "\n";
}

bool PowerUps::PowerBlock::CheckCollision(Rect& paddleRect)
{
	return this->rect.CheckCollision(paddleRect);
}

void PowerUps::PowerBlock::UpdatePowerBlock(float dt, Rect& playzone)
{
	this->rect.pos += glm::normalize(velocity) * speed * dt;
	if (rect.pos.y >= playzone.Bottom)
		DestroyPowerBlock();
}

void PowerUps::PowerBlock::Draw(SpriteRenderer* render)
{
	render->DrawSprite(texture, rect.pos, rect.size);
}
