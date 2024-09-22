#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;
uniform vec3 u_stencil_color;
out vec3 stencil_color;
void main()
{
    gl_Position = u_MVP * position;
    stencil_color = u_stencil_color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 stencil_color;
void main()
{   
    color = vec4(stencil_color,1.0);
};