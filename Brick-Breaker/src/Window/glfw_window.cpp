#include "glfw_window.h"

#include <iostream>

namespace Breaker
{
    Window::Window(const WinProps& props)
        : props(props)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, false);

        Init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    std::unique_ptr<Window> Window::CreateWindow(const WinProps& props)
    {
        auto wnd = std::make_unique<Window>(props);
        return wnd;
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();

        glViewport(0, 0, props.width, props.height);
        glfwSwapBuffers(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    bool Window::IsShouldClose()
    {
        return !glfwWindowShouldClose(window);
    }

    void Window::Init()
    {
        if (!glfwInit())
        {
            std::cerr << "Faied to initialize GLFW" << "\n";
        }

        window = glfwCreateWindow(props.width, props.height, props.name, NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << "\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glfwSwapInterval(1);

        const GLubyte* renderer = glGetString(GL_RENDERER); // GPU
        const GLubyte* vendor = glGetString(GL_VENDOR);     // Vendor
        const GLubyte* version = glGetString(GL_VERSION);   // OpenGL version

        std::cout << "Graphics Card Vendor: " << vendor << "\n";
        std::cout << "Renderer: " << renderer << "\n";
        std::cout << "OpenGL Version: " << version << "\n\n";

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}