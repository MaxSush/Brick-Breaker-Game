#include "glfw_window.h"

#include <iostream>

namespace Breaker
{
    Window::Window(const WinProps& props)
        : props(props),
        mouse(MouseListner::get())
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
        glfwDestroyCursor(MouseListner::get().cursor);
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
        mouse.CheckCursorInactivity(&props);

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

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glfwSetKeyCallback(props.window, KeyListner::key_callback);
        glfwSetCursorPosCallback(props.window, MouseListner::cursor_position_callback);
        glfwSetMouseButtonCallback(props.window, MouseListner::mouse_button_callback);
        glfwSetScrollCallback(props.window, MouseListner::scroll_callback);

        glfwSwapInterval(1);

        const GLubyte* renderer = glGetString(GL_RENDERER); // GPU
        const GLubyte* vendor = glGetString(GL_VENDOR);     // Vendor
        const GLubyte* version = glGetString(GL_VERSION);   // OpenGL version

        std::cout << "Graphics Card Vendor: " << vendor << "\n";
        std::cout << "Renderer: " << renderer << "\n";
        std::cout << "OpenGL Version: " << version << "\n\n";

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mouse.CreateCursor("assets/cursor.png");
        glfwSetCursor(props.window, mouse.cursor);
    }
}