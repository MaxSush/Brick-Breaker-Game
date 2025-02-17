# Define Game module target

add_library(Game STATIC
    Game.cpp
    GameObject/GameObject.cpp 
    GameObject/Ball.cpp
    GameObject/ParticleGenerator.cpp
    GameObject/Paddle.cpp 
    GameObject/Brick.cpp 
    Process/Level.cpp
    Process/GamePostProcessing.cpp 
    Process/PowerUps.cpp
    Process/MenuWindow.cpp)

if(WIN32)
    target_link_directories(Game PUBLIC "${OPENAL_DIR}/lib")
    target_link_libraries(Game PUBLIC glfw opengl32 SndFile::sndfile Utility OpenAL32)
elseif(UNIX)
    find_package( OpenGL REQUIRED )
    target_link_libraries(Game PUBLIC glfw Utility ${OPENGL_LIBRARIES})
endif()


# Add any required libraries for the Game module (if needed)
# Example: target_link_libraries(Game PRIVATE some_library)
