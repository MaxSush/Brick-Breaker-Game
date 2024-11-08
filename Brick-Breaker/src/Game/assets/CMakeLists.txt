# Set up a list of shader and texture resources to copy
set(SHADER_FILES
    shaders/cubeShader.fg
    shaders/cubeShader.vs
)

set(TEXTURE_FILES
    textures/background.jpg
    textures/ball.png
)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/assets)

# Create the output directory if it doesn't exist
file(MAKE_DIRECTORY ${OUTPUT_DIR})

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
