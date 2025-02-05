#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 texCord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = texCord.xy;
    gl_Position = projection * model * vec4(aPos.xy, 0.0, 1.0);
}
