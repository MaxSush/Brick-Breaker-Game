#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>

#include "Application.h"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        auto* app = new Breaker::Application;

        app->Run();

        delete app;
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        char buffer[256];

        #ifdef _WIN32
            strerror_s(buffer, sizeof(buffer), errno);
        #else
            strerror_r(errno, buffer, sizeof(buffer));
        #endif

        std::cerr << "Error [ " << errno << " ]: " << buffer << std::endl;
    }

    // auto* app = new Breaker::Application; app->Run(); 

    return 0;
}