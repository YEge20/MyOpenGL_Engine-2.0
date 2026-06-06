#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcood;
layout(location = 2) in vec4 VerColor;

uniform mat4 u_MVP;

out vec2 v_texcood;
out vec4 v_VerColor;
void main()
{
    gl_Position = u_MVP * position;
    v_texcood = texcood;
    v_VerColor = VerColor;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform float u_red;

in vec2 v_texcood;
in vec4 v_VerColor;
void main()
{   
    color = mix(texture(u_texture0 , v_texcood),texture(u_texture1,v_texcood),0.25) + v_VerColor * u_red;
}