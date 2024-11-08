#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject/Ball.h"

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

        void PrintWindowProps();

    private:
        const WinProps* props;

        GameState state = GameState::GAME_ACTIVE;
        SpriteRenderer* sprite = nullptr;


        Ball* ball = nullptr;
    };
}