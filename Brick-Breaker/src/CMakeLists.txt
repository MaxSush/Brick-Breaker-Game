

set(CPP_SOURCES
    main.cpp
    Application.cpp  
    Window/glfw_window.cpp
    glad.c
  Window/KeyListner.cpp
)

add_subdirectory("assets")

add_subdirectory("Utility")

add_subdirectory("Game")

add_subdirectory("Menu")


add_executable(Far-Annoyed ${CPP_SOURCES})

target_include_directories(Far-Annoyed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Far-Annoyed PRIVATE Game Menu)

if(WIN32)
    add_custom_command(TARGET Far-Annoyed POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENAL_DIR}/bin/OpenAL32.dll"
        $<TARGET_FILE_DIR:Far-Annoyed>)

    add_custom_command(TARGET Far-Annoyed POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SNDFILE_DIR}/bin/sndfile.dll"
        $<TARGET_FILE_DIR:Far-Annoyed>)
endif()