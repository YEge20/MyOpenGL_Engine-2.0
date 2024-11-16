#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;
void main()
{
    gl_Position = u_MVP * position;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform vec3 u_block_color;
void main()
{
    color = vec4(u_block_color,1.0);
}