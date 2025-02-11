# Set up a list of shader and texture resources to copy
set(LEVEL_FILES
    levels/1level.lvl
)

set(SHADER_FILES
    shaders/cubeShader.fg
    shaders/cubeShader.vs
    shaders/particle.fg
    shaders/particle.vs
    shaders/postProcessing.vs
    shaders/postProcessing.fg
)

set(TEXTURE_FILES
    textures/background.jpg
    textures/ball.png
    textures/particle.png
    textures/paddle.png
    textures/brick.png
    textures/solid.png
    textures/bevel.png
    textures/powerup_passthrough.png
    textures/powerup_chaos.png
    textures/powerup_confuse.png
    textures/powerup_increase.png
    textures/powerup_speed.png
    textures/powerup_sticky.png
    textures/menu.jpg
    textures/menu_exit.png
    textures/menu_play.png
)

set(AUDIO_FILES
    audio/bleep.wav
    audio/bleep.mp3
    audio/powerup.wav
    audio/solid.wav
    audio/breakout.mp3
    audio/menu.wav
)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/assets)

# Create the output directory if it doesn't exist
file(MAKE_DIRECTORY ${OUTPUT_DIR})

# Copy levels to the output directory
foreach(level ${LEVEL_FILES})
    get_filename_component(level_name ${level} NAME)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${level} ${OUTPUT_DIR}/${level_name} COPYONLY)
endforeach()

# Copy shaders to the output directory
foreach(shader ${SHADER_FILES})
    get_filename_component(shader_name ${shader} NAME)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${shader} ${OUTPUT_DIR}/${shader_name} COPYONLY)
endforeach()

# Copy textures to the output directory
foreach(texture ${TEXTURE_FILES})
    get_filename_component(texture_name ${texture} NAME)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${texture} ${OUTPUT_DIR}/${texture_name} COPYONLY)
endforeach()

foreach(audio ${AUDIO_FILES})
    get_filename_component(audio_name ${audio} NAME)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${audio} ${OUTPUT_DIR}/${audio_name} COPYONLY)
endforeach()
