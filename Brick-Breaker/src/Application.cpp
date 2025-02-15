#include "Application.h"
#include <iostream>

namespace Breaker
{
    Application::Application()
    {
        wnd = Window::CreateWindow();
        game = std::make_unique<Game>(wnd->GetWindowProps());
        menu = std::make_unique<Menu>();
        lvl_menu = std::make_unique<LevelMenu>();

        last = std::chrono::steady_clock::now();
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        int lvl = 0;
        bool levelLoaded = false;

        game->Init();
        menu->Init();
        lvl_menu->Init();
        while (wnd->IsShouldClose())
        {
            glfwPollEvents();
            FrameCounter();

            switch (gamestate)
            {
            case GameState::GAME_MENU:
                menu->Update(dt);
                menu->Render();
                menu->GetGameState(gamestate);
                break;
            case GameState::GAME_LEVEL_MENU:
                lvl_menu->LevelUpdate(dt);
                lvl_menu->LevelRender();
                lvl = lvl_menu->GetLevel();
                lvl_menu->GetGameState(gamestate);
                levelLoaded = false;
                break;
            case GameState::GAME_ACTIVE:
                std::cout << lvl << "\n";
                if (!levelLoaded) {
                    game->LoadLevel(lvl);
                    levelLoaded = true;
                }
                game->Update(dt);
                game->Render();
                break;
            case GameState::GAME_WIN:
                break;
            case GameState::GAME_EXIT:
                wnd->OnUpdate();
                return;
            }
            // Replace for game over logic 
            if (KeyListner::IsKeyPressedOnce(GLFW_KEY_BACKSPACE))
            {
                gamestate = GameState::GAME_LEVEL_MENU;
                ResourceManager::StopAudio("breakout");
            }
            wnd->OnUpdate();
        }
    }

    void Application::FrameCounter()
    {
        const auto old = last;
        last = std::chrono::steady_clock::now();
        const std::chrono::duration<float> frametime = last - old;
        dt = frametime.count();
    }
}