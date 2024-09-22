#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texture_position;
layout(location = 2) in vec3 A_normal;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_copy;

out vec2 texture_color;
out vec3 normal;
out vec3 Fragpos;
void main()
{
    gl_Position = u_MVP * position;    
    texture_color = texture_position;
    normal = A_normal;
    Fragpos = vec3(u_copy * u_model * position);//把顶点全部都转换成世界坐标
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_view_position;// 观察者的位置

in vec2 texture_color;
in vec3 normal;
in vec3 Fragpos;

//设置材料不同方式照射的属性
struct Metrial{
    sampler2D diffuse;//环境光与漫反射的纹理
    sampler2D specular;//镜面反射的颜色
    float shinness;//镜面反射的散射半径
};
uniform Metrial u_material;
//设置光源的属性
struct Light{
    vec3 position;//光源的位置
    vec3 ambientcolor;//发出环境光的颜色,一定要暗
    vec3 diffuse;//发出漫反射光的颜色,注意不要太暗
    vec3 specular;//发出镜面反射的颜色,亮一点
};
#define PointLight 6
uniform Light u_light[PointLight];
//设置手电筒的属性
struct FlashLight{
    vec3 position;//手电筒的位置
    vec3 diract;//手电筒的方向
    float cutoff;//光束的照射模糊边缘余弦夹角
    float OutCutoff;//光束的最大余弦夹角
    int flashSwitch;//手电筒的开关
};
uniform FlashLight u_flash;
//设置光线的距离衰减属性
struct LightAttenuatuon{
    float C;//设置光线距离衰减常数
    float L;//设置光线距离衰减一次项系数
    float Q;//设置光线距离衰减二次项系数
};
uniform LightAttenuatuon u_PLight_ATT;//点光源的距离衰减
uniform LightAttenuatuon u_FLight_ATT;//手电筒的距离衰减

//点光源计算函数
vec3 LightFun(Light light , vec3 view_position)
{
//点光源距离衰减计算
    float distance = length(light.position - Fragpos);
    float attenuation = 1.0 / (u_PLight_ATT.C + u_PLight_ATT.L * distance + u_PLight_ATT.Q * pow(distance , 2.0));
//计算环境光
    vec3 environment = light.ambientcolor * vec3(texture(u_material.diffuse , texture_color));
//计算漫反射光
    vec3 nor = normalize(normal);
    vec3 light_diract = normalize(light.position - Fragpos);
    float diff1 = max(dot(nor , light_diract),0.0);
    vec3 diffuse = light.diffuse * diff1 * vec3(texture(u_material.diffuse , texture_color));
//计算镜面反射高光
    vec3 view_diract = normalize(view_position - Fragpos);
    vec3 HDir = normalize(view_diract + light_diract);
    float spec =  pow(max(dot(nor , HDir),0.0),u_material.shinness);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular,texture_color));
//输出光照效果
    vec3 result = (diffuse + environment + specular) * attenuation;
    return result;
};

//手电筒计算函数
vec3 FlashFun(FlashLight flash)
{
//手电筒距离衰减计算
    float distance = length(flash.position - Fragpos);
    float attenuation = 1.0 / (u_FLight_ATT.C + u_FLight_ATT.L * distance + u_FLight_ATT.Q * pow(distance , 2.0));
//计算手电筒的光照
    vec3 flash_diract = normalize(Fragpos - flash.position);
    float cosTheta = dot(flash_diract , flash.diract);
    float epsilo = flash.cutoff - flash.OutCutoff;
    float intensity = clamp((flash.cutoff - cosTheta) / epsilo , 0.0 , 1.0);
    vec3 flash_result;
    if(cosTheta >= flash.cutoff && flash.flashSwitch > 0)
        flash_result = vec3(texture(u_material.diffuse , texture_color)) * cosTheta * intensity * attenuation;
    return flash_result;
};

void main()
{
    vec3 LightResult;
    for(int i = 0 ; i < PointLight ; i++)
        LightResult += LightFun(u_light[i] , u_view_position);
    vec3 FlashResult = FlashFun(u_flash);
    color = vec4(LightResult , 1.0) + vec4(FlashResult , 1.0);
}