#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rect.h"
#include "Manager/ResourceManager.h"
#include "Manager/SpriteRenderer.h"
#include "GameObject/Ball.h"
#include "GameObject/ParticleGenerator.h"
#include "GameObject/Paddle.h"
#include "Process/Level.h"
#include "Process/GamePostProcessing.h"
#include "Process/PowerUps.h"
#include "Process/MenuWindow.h"

namespace Breaker
{
    struct WinProps;

    class Game
    {
    public:
        Game(const WinProps* props);
        ~Game();
        void Init();
        void Update(float dt);
        void Render();

        void ProcessInput(float dt);
        void LoadLevel(int lvl);
        void GetState(GameState& state);

    private:
        static constexpr float offset = 10.0f * 1.5;
        float shakeTime = 0.0f;
        int lives = 5;
        const WinProps* props;
        Rect playzone;
        std::vector<Brick>* bricks = nullptr;

        GameState gamestate = GameState::GAME_ACTIVE;
        GameWindow window = GameWindow::GAME_PLAY;
        SpriteRenderer* sprite = nullptr;
        Ball* ball = nullptr;
        ParticleGenerator* p_generator = nullptr;
        Paddle* paddle = nullptr;
        GameLevel* level = nullptr;
        GameEffects* effects = nullptr;
        MenuWindow* menu_window = nullptr;

        PowerUps powerups;

        void FixBallBrickCollision();
        void ActivatePowerUps(PowerUps::PowerBlock* block);
    };
}