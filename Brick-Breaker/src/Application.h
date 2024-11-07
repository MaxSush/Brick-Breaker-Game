#pragma once
#include "Window/glfw_window.h"
#include "Game/Game.h"

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

        float dt = 0.0f;
        std::chrono::steady_clock::time_point last;
    };
}