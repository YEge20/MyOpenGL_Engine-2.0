#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec3 normalize;

uniform mat4 u_MVP;
uniform mat4 u_model;

out vec3 v_nor;
out vec3 v_Fragpos;
void main()
{
    gl_Position = u_MVP * position;
    v_nor = normalize;
    v_Fragpos = vec3(u_model * position);
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

//设置光源属性
struct Light{
    vec3 position;
    vec3 color;
};

uniform Light u_light;
uniform vec3 u_view_position;
uniform float u_strength_light;//平行光的强度
uniform float u_alpha;//控制雨滴逐渐消失的过程

in vec3 v_nor;
in vec3 v_Fragpos;
void main()
{
    //归一化法线方向：
    vec3 nor = normalize(v_nor);
    //计算平行光的方向：
    vec3 LightDir = normalize(vec3(0.0 , -120.0 , 0.0) - u_light.position);
    //设置环境光：
    vec3 environment = u_light.color * vec3(0.3);
    //计算漫反射光：
    vec3 LightDir_2 = normalize(v_Fragpos - u_light.position);
    float diff = 0.7 * max(dot(-LightDir_2, vec3(0.0,1.0,0.0)), 0.0);
    vec3 diffuse = 1.5 * u_strength_light * diff * u_light.color;
    //计算镜面反射光：
    vec3 view_diract = normalize(u_view_position - v_Fragpos);
    vec3 HDir = normalize(-LightDir + view_diract);
    float spec = pow(max(dot(HDir, nor), 0.0), 32);
    vec3 specular = u_strength_light * spec * u_light.color;
    //输出：
    color = vec4(1.0,1.0,1.0,0.4) * vec4(environment + diffuse + specular, u_alpha);
}