add_library(Menu STATIC 
	Menu.cpp
    LevelMenu.cpp 
    "Framebuffer.cpp" 
)

if(WIN32)
    target_link_libraries(Menu PUBLIC glfw opengl32 Utility)
elseif(UNIX)
    find_package( OpenGL REQUIRED )
    target_link_libraries(Menu PUBLIC glfw ${OPENGL_LIBRARIES})
endif()