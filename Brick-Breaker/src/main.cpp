#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
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
        strerror_s(buffer, sizeof(buffer), errno);
        std::cerr << "Error [ " << errno << " ]: " << buffer << std::endl;
    }

    // auto* app = new Breaker::Application; app->Run(); 

    return 0;
}