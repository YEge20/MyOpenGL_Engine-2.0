#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 u_MVP;

out VS_OUT{
    vec2 texcoord;
}vs_out;

void main()
{
    gl_Position = u_MVP * position;
    vs_out.texcoord = texcoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture;

in VS_OUT{
    vec2 texcoord;
}fs_in;

void main()
{   
    vec4 texture_color = texture(u_texture, fs_in.texcoord);
    if(texture_color.a == 0.0)
        discard;
    color = vec4(vec3(1.0),1.0);
};