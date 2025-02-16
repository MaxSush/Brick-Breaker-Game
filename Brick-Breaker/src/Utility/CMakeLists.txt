add_library(Utility STATIC
    Rect.cpp
    SHADER.cpp
    TEXTURE.cpp
    stb_image.cpp
    VAO.cpp
    VBO.cpp
    EBO.cpp
    Manager/SpriteRenderer.cpp
    Manager/ResourceManager.cpp
 "Manager/Framebuffer.cpp" "Manager/Framebuffer.h")

target_include_directories(Utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    target_link_libraries(Utility PUBLIC glfw opengl32 )
elseif(UNIX)
    find_package( OpenGL REQUIRED )
    target_link_libraries(Utility PUBLIC glfw ${OPENGL_LIBRARIES})
endif()