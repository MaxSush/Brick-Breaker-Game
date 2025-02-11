#pragma once
#include "../GameObject/GameObject.h"
#include <vector>
#include "Manager/ResourceManager.h"
#include "GamePostProcessing.h"
#include "../GameObject/Ball.h"

enum class PowerType
{
	SPEED,
	CHAOS,
	CONFUSE,
	STICKY,
	PASS_THROUGH,
	PAD_SIZE_INCREASE,
	PAD_SIZE_DECREASE
};

class PowerUps
{
public:
	class PowerBlock : private GameObject
	{
	public:
		PowerBlock(glm::vec2 pos, glm::vec2 size, const Texture& texture, PowerType type, float duration);
		void DestroyPowerBlock();
		bool CheckCollision(Rect& paddleRect);
		void UpdatePowerBlock(float dt, Rect& playzone);
		void Draw(SpriteRenderer* render) override;
		bool activated = false;
		bool destroyed = false;
		PowerType type;
		float duration = 0.0f;
	private:
		glm::vec2 velocity = { 0,1 };
		float speed = 200;
	};
public:
	PowerUps();
	void SpawnPowerUps(Rect& brickBlock);
	void UpdatePowerUps(float dt, Rect& playzone, Ball* ball, GameEffects* effects);
	PowerBlock* CheckCollision(Rect& paddleRect);
	void DrawPowerUps(SpriteRenderer* render);
	bool IsOtherPowerUpsActivated(PowerType type);
private:
	std::vector<PowerBlock> powerups;
};
