#include "Application.h"
#include <iostream>

namespace Breaker
{
    Application::Application()
    {
        wnd = Window::CreateWindow();
        game = std::make_unique<Game>(wnd->GetWindowProps());
        last = std::chrono::steady_clock::now();
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        game->Init();
        game->PrintWindowProps();
        while (wnd->IsShouldClose())
        {
            FrameCounter();
            // std::cout << "Frametime : " << dt << "\n";

            game->Update(dt);
            
            game->Render();

            wnd->OnUpdate();

        };
    }

    void Application::FrameCounter()
    {
        const auto old = last;
        last = std::chrono::steady_clock::now();
        const std::chrono::duration<float> frametime = last - old;
        dt = frametime.count();
    }
}