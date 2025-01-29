#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utility/Rect.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject/Ball.h"
#include "GameObject/ParticleGenerator.h"
#include "GameObject/Paddle.h"
#include "Process/Level.h"

namespace Breaker
{
    enum class GameState
    {
        GAME_MENU,
        GAME_ACTIVE,
        GAME_WIN,
        GAME_EXIT
    };

    struct WinProps;

    class Game
    {
    public:
        Game(const WinProps* props);
        ~Game();
        void Init();
        void Update(float dt);
        void Render();
        void DoCollision();

        // imgui
        void DrawImGuiLayer();

    private:
        static constexpr float offset = 20.0f;
        const WinProps* props;
        Rect playzone;
        std::vector<Brick>* bricks = nullptr;

        GameState state = GameState::GAME_ACTIVE;
        SpriteRenderer* sprite = nullptr;
        Ball* ball = nullptr;
        ParticleGenerator* p_generator = nullptr;
        Paddle* paddle = nullptr;
        GameLevel* level = nullptr;

    };
}