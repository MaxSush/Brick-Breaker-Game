

set(CPP_SOURCES
    main.cpp
    Application.cpp  
    Window/glfw_window.cpp
    glad.c
  "Window/KeyListner.cpp")

add_subdirectory("Game")

add_executable(Far-Annoyed ${CPP_SOURCES})

target_link_libraries(Far-Annoyed PRIVATE Game)