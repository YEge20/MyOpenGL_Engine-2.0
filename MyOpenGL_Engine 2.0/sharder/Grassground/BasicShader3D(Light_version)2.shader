#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 A_normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_rota;

out vec2 v_texcoord;
out vec3 v_nor;
out vec3 v_Fragpos;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = texcoord;
    v_nor = vec3(u_rota * vec4(A_normal , 1.0));//添加旋转功能后法线也要旋转
    v_Fragpos = vec3(u_model * position);//让每个顶点都落在世界坐标上
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//设置光源属性
struct Light{
    vec3 diraction;
    vec3 color;
};

uniform Light u_light;
uniform sampler2D u_sampler;
uniform sampler2D u_sampler_light_ore_pbr;
uniform sampler2D u_sampler_reflect_pbr;
uniform vec3 u_view_position;

in vec2 v_texcoord;
in vec3 v_nor;
in vec3 v_Fragpos;
void main()
{   
//归一化法线方向：
    vec3 nor = normalize(v_nor);
//计算光的路径：
    vec3 LightDir = normalize(-u_light.diraction);
//计算漫反射：
    float diff = max(dot(-LightDir , nor),0.0);
    vec3 diffuse = (diff + 0.25) * u_light.color;
//计算镜面反射：
    vec3 view_diract = normalize(u_view_position - v_Fragpos);
    vec3 refl_light_diract = reflect(LightDir , nor);
    float spec = pow(max(dot(view_diract , refl_light_diract) , 0.0),32);
    vec3 specular = spec * u_light.color;
//光源效果输出：
    color = texture(u_sampler_reflect_pbr , v_texcoord) * vec4(specular , 1.0) + texture(u_sampler_light_ore_pbr , v_texcoord) * vec4(1.4,1.4,1.4,1.0) + texture(u_sampler , v_texcoord) * vec4(diffuse , 1.0);
}