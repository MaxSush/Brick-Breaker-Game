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

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        std::cout << glfwGetVersionString() << "\n";

        Init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(props.window);
        glfwTerminate();
    }

    std::unique_ptr<Window> Window::CreateWindow(const WinProps& props)
    {
        auto wnd = std::make_unique<Window>(props);
        return wnd;
    }

    void Window::OnUpdate()
    {
        glfwGetWindowSize(props.window, &props.width, &props.height);
        glViewport(0, 0, props.width, props.height);
        glfwSwapBuffers(props.window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    bool Window::IsShouldClose() const
    {
        return !glfwWindowShouldClose(props.window);
    }

    const WinProps* Window::GetWindowProps() const
    {
        return &props;
    }

    void Window::Init()
    {
        if (!glfwInit())
        {
            std::cerr << "Faied to initialize GLFW" << "\n";
        }

        props.window = glfwCreateWindow(props.width, props.height, props.name, NULL, NULL);
        if (!props.window)
        {
            std::cerr << "Failed to create GLFW window" << "\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(props.window);

        glfwSetKeyCallback(props.window, KeyListner::key_callback);

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