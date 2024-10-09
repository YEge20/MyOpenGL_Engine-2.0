#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 point_color;

uniform mat4 u_MVP;

out vec4 v_point_of_color;
void main()
{
    gl_Position = u_MVP * position;
    v_point_of_color = point_color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_point_of_color;
void main()
{   
    color = vec4(1.2 * vec3(v_point_of_color),1.0);
};