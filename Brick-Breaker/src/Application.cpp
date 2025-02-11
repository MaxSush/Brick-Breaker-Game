#include "Application.h"
#include <iostream>

namespace Breaker
{
    Application::Application()
    {
        wnd = Window::CreateWindow();
        game = std::make_unique<Game>(wnd->GetWindowProps());
        menu = std::make_unique<Menu>();
        last = std::chrono::steady_clock::now();
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        game->Init();
        menu->Init();
        while (wnd->IsShouldClose())
        {
            glfwPollEvents();

            FrameCounter();
            // std::cout << "Frametime : " << dt << "\n";

            menu->Update(dt);

            //game->Update(dt);
            menu->Render();
            
            //game->Render();

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