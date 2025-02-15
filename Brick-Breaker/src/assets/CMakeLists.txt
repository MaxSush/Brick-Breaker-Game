set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/assets)

# Create the output directory if it doesn't exist
file(MAKE_DIRECTORY ${OUTPUT_DIR})

# Copy levels to the output directory
file(GLOB LEVEL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/levels/*")
file(COPY ${LEVEL_FILES} DESTINATION ${OUTPUT_DIR})

# Copy shaders to the output directory
file(GLOB SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*")
file(COPY ${SHADER_FILES} DESTINATION ${OUTPUT_DIR})

# Copy textures to the output directory
file(GLOB TEXTURE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/textures/*")
file(COPY ${TEXTURE_FILES} DESTINATION ${OUTPUT_DIR})

file(GLOB AUDIO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/audio/*")
file(COPY ${AUDIO_FILES} DESTINATION ${OUTPUT_DIR})
