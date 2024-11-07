#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace Breaker
{
    typedef unsigned int uint;

    struct WinProps
    {
        uint width;
        uint height;
        const char* name;
        WinProps(uint w = 900, uint h = 700, const char* name = "Brick-Breaker")
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
        bool IsShouldClose();

    private:
        GLFWwindow* window;
        WinProps props;

        void Init();
    };
}