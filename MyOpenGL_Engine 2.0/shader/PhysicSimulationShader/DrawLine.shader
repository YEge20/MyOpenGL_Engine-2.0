#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 u_MVP;
out vec4 v_color;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    v_color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;

void main()
{   
    color = v_color;
};