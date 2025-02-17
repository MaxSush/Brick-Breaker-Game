#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "KeyListner.h"
#include "MouseListner.h"

namespace Breaker
{
    struct WinProps
    {
        int width;
        int height;
        GLFWwindow* window = nullptr;
        const char* name;
        
        WinProps(int w = 900, int h = 700, const char* name = "Brick-Breaker")
            : width(w), height(h), name(name)
        {
        }
    };

    class Window
    {
    public:
        Window(const WinProps& props);
        ~Window();

        static std::unique_ptr<Window> CreateWindow(const WinProps& props = WinProps());

        void OnUpdate();
        bool IsShouldClose() const;
        const WinProps* GetWindowProps() const;

    private:
        WinProps props;
        MouseListner& mouse;

        void Init();
    };
}