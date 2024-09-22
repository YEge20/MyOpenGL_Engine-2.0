#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcood;
layout(location = 2) in vec4 pointcolor;
layout(location = 3) in float top_button;

uniform mat4 u_MVP;
uniform mat4 u_wave;

out vec2 v_texcood;
out vec4 v_pointcolor;
void main()
{
    if(top_button == 1.0)
        gl_Position =  u_MVP * u_wave* position;
    else 
        gl_Position = u_MVP * position;
    v_texcood = texcood;
    v_pointcolor = pointcolor;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture0;
uniform float u_grass_flower;
uniform float u_red;

in vec2 v_texcood;
in vec4 v_pointcolor;
void main()
{   
    vec4 texColor = texture(u_texture0,v_texcood);
    if(texColor.a < 0.1)
        discard;
    if(u_grass_flower == 1.0)
        color = texColor * v_pointcolor + vec4(0.2,0.1,0.0,1.0) * u_red;
    else
        color = texColor;
}