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
