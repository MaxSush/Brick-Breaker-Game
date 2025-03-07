#pragma once
#include "Window/glfw_window.h"
#include "Game/Game.h"
#include "Menu/Menu.h"
#include "Menu/LevelMenu.h"

#include <chrono>
#include <memory>

namespace Breaker
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
        void FrameCounter();

    private:
        std::unique_ptr<Window> wnd = nullptr;
        std::unique_ptr<Game> game = nullptr;
        std::unique_ptr<Menu> menu = nullptr;
        std::unique_ptr<LevelMenu> lvl_menu = nullptr;

        float dt = 0.0f;
        std::chrono::steady_clock::time_point last;

        GameState gamestate = GameState::GAME_MENU;
    };
}