#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 u_MVP;
out vec2 v_texcoord;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = texcoord * vec2(-1.0,1.0);
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_texcoord;
uniform sampler2D u_screenTexture;
uniform float u_alpha;


void main()
{
    const float offset = 1.0 / 1000.0;
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),   vec2( 0.0f,    offset),   vec2( offset,  offset), 
        vec2(-offset,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset,  0.0f), 
        vec2(-offset, -offset),   vec2( 0.0f,   -offset),   vec2( offset, -offset)
    );

    float kernel[9] = float[](
         1.0, 1.0, 1.0,
         1.0,-8.0, 1.0,
         1.0, 1.0, 1.0
    );

    vec3 SampleTex[9];
    for(int i = 0; i < 9 ;i++)
    {
        SampleTex[i] = vec3(texture(u_screenTexture, v_texcoord.st + offsets[i]));
    };

    vec3 finalcol = vec3(0.0);
    for(int i = 0; i < 9 ; i++)
    {
        finalcol += SampleTex[i] * kernel[i];
    };

    color = vec4(finalcol ,u_alpha);

    //vec4 testColor = vec4(vec3(texture(u_screenTexture, v_texcoord)), u_alpha);
    //color = testColor;
}