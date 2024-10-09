#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec4 point_color;
layout(location = 3) in float index_texture;

uniform mat4 u_MVP1;
uniform mat4 u_MVP2;

out vec2 colorOftexcoord;
out vec4 v_point_of_color;
out float v_index_texture;

void main()
{
    gl_Position = u_MVP1 * position;
    colorOftexcoord = texcoord;
    v_point_of_color = point_color;
    v_index_texture = index_texture;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_changecolor;
uniform sampler2D u_texture2[2];

in vec2 colorOftexcoord;
in vec4 v_point_of_color;
in float v_index_texture;

void main()
{
    int index = int(v_index_texture);
    vec4 object = texture(u_texture2[index],colorOftexcoord);
    if(object.a == 0.0)
        discard;
    color =  u_changecolor + object + v_point_of_color;    
};