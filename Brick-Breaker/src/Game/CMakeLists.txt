# Define Game module target

add_subdirectory(assets)

add_library(Game STATIC
    Game.cpp
    ResourceManager.cpp
    Utility/SHADER.cpp
    Utility/TEXTURE.cpp
    Utility/stb_image.cpp
    Utility/VAO.cpp
    Utility/VBO.cpp
    Utility/EBO.cpp
    SpriteRenderer.cpp
    GameObject/GameObject.cpp 
    GameObject/Ball.cpp
 "Utility/Rect.h")


target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    target_link_libraries(Game PUBLIC glfw opengl32)
elseif(UNIX)
    find_package( OpenGL REQUIRED )
    target_link_libraries(Game PUBLIC glfw ${OPENGL_LIBRARIES})
endif()

# Add any required libraries for the Game module (if needed)
# Example: target_link_libraries(Game PRIVATE some_library)
