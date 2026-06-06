#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

out vec3 v_texcoord;

void main()
{
    vec4 pos = u_MVP * position;
    gl_Position = pos.xyww;
    v_texcoord = vec3(position.x,-position.y,position.z);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform samplerCube u_skybox;
uniform vec4 u_light;

in vec3 v_texcoord;

void main()
{
    color = texture(u_skybox,v_texcoord) * u_light;
}