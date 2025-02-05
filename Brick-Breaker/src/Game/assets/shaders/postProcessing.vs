#version 460 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform bool chaos;
uniform bool confuse;
uniform bool shake;
uniform float time;

void main()
{
    gl_Position = vec4(vertex.xy, 0.0f, 1.0f); 
    vec2 texture = vertex.zw;
    if(chaos)
    {
        float strength = 0.2;
        vec2 pos = vec2(texture.x + sin(time) * strength, texture.y + cos(time) * strength / 4.0f);        
        TexCoords = pos;
    }
    else if(confuse)
    {
        TexCoords = vec2(1.0 - texture.x, 1.0 - texture.y);
    }
    else
    {
        TexCoords = texture;
    }
    if (shake)
    {
        float strength = 0.007;                             // Reduce strength for shorter displacement
        gl_Position.x += cos(time * 100.0) * strength;       // Increase frequency
        gl_Position.y += sin(time * 150.0) * strength;       // Use sin for variation
       
    }
}