#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;
uniform vec3 test_color;

out vec3 v_test_color;
void main()
{
    gl_Position = u_MVP * position;
    v_test_color = test_color;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec3 v_test_color;
void main()
{
    color = vec4(v_test_color,1.0);
}