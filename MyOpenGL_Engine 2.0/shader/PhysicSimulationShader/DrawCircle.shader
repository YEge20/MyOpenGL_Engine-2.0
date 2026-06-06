#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 RGB;
layout(location = 2) in vec3 LocalPos;

struct VertexOutput
{
    vec3 LocalPosition;
    vec3 Circle_color;
};
out VertexOutput Circle;

uniform mat4 u_MVP;
uniform mat4 u_Rota;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    Circle.LocalPosition = vec3(u_Rota * vec4(LocalPos, 1.0));
    Circle.Circle_color = RGB;
};

#shader fragment
#version 330 core

struct VertexOutput
{
    vec3 LocalPosition;
    vec3 Circle_color;
};
in VertexOutput Circle;

layout(location = 0) out vec4 color;

uniform float u_Fade;

void main()
{   
    float fade = smoothstep(0.01,1.0,u_Fade);
    float dis = 1.0 - length(Circle.LocalPosition);
    float alpha = smoothstep(0.0, fade, dis);
    alpha *= smoothstep(1.0 + fade, 1.0, dis);
    if(alpha <= 0.01)
       discard;

    color = vec4(Circle.Circle_color, alpha);
};