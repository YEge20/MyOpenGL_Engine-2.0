#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec3 nor;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_rota;

out vec3 v_FragPos;
out vec3 v_nor;
void main()
{
    gl_Position = u_MVP * position;
    v_FragPos = vec3(u_model * position);
    v_nor = normalize(vec3(u_rota * vec4(nor, 1.0)));
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_Cam_Pos;
uniform samplerCube sky;

in vec3 v_FragPos;
in vec3 v_nor;
void main()
{
    vec3 look_Dir = v_FragPos - u_Cam_Pos;
    vec3 reflect_Dir = reflect(look_Dir, v_nor);
    color = texture(sky, reflect_Dir);
}