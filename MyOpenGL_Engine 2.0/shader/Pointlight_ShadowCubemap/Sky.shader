#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

out vec3 v_texcooed;
void main()
{
    v_texcooed = vec3(position);
    gl_Position = (u_MVP * position).xyww;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_texcooed;
uniform samplerCube u_sky;
void main()
{   
    color = texture(u_sky , v_texcooed);
}