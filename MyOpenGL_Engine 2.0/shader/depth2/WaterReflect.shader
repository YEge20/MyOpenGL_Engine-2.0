#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 u_MVP;

out vec2 v_texcoord;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = texcoord * vec2(-1.0, 1.0);
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform float u_alpha;
uniform sampler2D u_ReflectTexture;

in vec2 v_texcoord;

void main()
{
    vec3 finalcol = vec3(texture(u_ReflectTexture, v_texcoord));
    if(finalcol.rgb == vec3(0.0,0.0,0.0))
        discard;
    color = vec4(finalcol,u_alpha);
}