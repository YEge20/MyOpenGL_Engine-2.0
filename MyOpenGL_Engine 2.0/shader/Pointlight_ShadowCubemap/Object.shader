#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 u_MVP;

out vec2 v_texcoord;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = texcoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_mirror_texture;
uniform float u_alpha;

in vec2 v_texcoord;
void main()
{
    color = vec4(vec3(texture(u_mirror_texture, v_texcoord)), u_alpha);
}