#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoords;

uniform mat4 u_MVP;
out vec2 v_texcoord;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = texcoords;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_texcoord;

uniform sampler2D u_texture;
void main()
{
    color = texture(u_texture, v_texcoord);
}