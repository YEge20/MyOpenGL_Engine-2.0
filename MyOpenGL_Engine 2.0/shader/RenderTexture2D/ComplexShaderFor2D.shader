#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 nor;

uniform mat4 u_MVP;

out vec2 v_Texcoord;

void main()
{
    gl_Position = u_MVP * position;
    v_Texcoord = texcoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture;

in vec2 v_Texcoord;

void main()
{
    vec4 object = texture(u_texture, v_Texcoord);
    if(object.a == 0.0)
        discard;
    color = object;    
};