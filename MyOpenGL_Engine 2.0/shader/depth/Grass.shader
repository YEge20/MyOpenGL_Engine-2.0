#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcood;
layout(location = 2) in vec4 pointcolor;
layout(location = 3) in float top_button;
layout(location = 4) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_wave;
uniform mat4 u_LightMartix;
uniform mat4 u_model;

out vec2 v_texcood;
out vec4 v_pointcolor;
out vec3 v_normal;
out vec4 v_Fragpos_LightSpace;

void main()
{
    if(top_button == 1.0)
        gl_Position =  u_MVP * u_wave * position;
    else 
        gl_Position = u_MVP * position;
    v_texcood = texcood;
    v_pointcolor = pointcolor;
    v_normal = normal;
    v_Fragpos_LightSpace = u_LightMartix * u_model * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//设置光源属性
struct Light{
    vec3 position;
    vec3 color;
};

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;//深度图
uniform float u_grass_flower;
uniform float u_red;
uniform float u_white;
uniform Light u_light;
uniform float u_strength_light;//平行光的强度


in vec2 v_texcood;
in vec4 v_pointcolor;
in vec3 v_normal;
in vec4 v_Fragpos_LightSpace;

float ShadowCaculation(vec4 v_Fragpos_LightSpace , float bias)
{
    //执行透视分割并把数值转换成0~1的范围
    vec3 procoord = v_Fragpos_LightSpace.xyz / v_Fragpos_LightSpace.w;
    procoord = procoord * 0.5 + 0.5;
    //获取离光源最近的深度值
    float closestDepth = texture(u_texture1 , procoord.xy).r;
    //获取当前深度值
    float currentDepth = procoord.z;
    //判断是否出于阴影之中:
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    vec3 LightDir_2 = normalize(u_light.position - vec3(0.0 , -120.0 , 0.0));
    vec3 nor_2 = normalize(v_normal);
    float degree = max(dot(LightDir_2 , nor_2) , 0.0);
    if(degree > 0.996)
        shadow = 1.0 * (1.0 - degree);
    return shadow;
}

void main()
{   
    vec4 texColor = texture(u_texture0,v_texcood);
    if(texColor.a < 0.1)
        discard;
//区分花和草的类型
    vec4 result_1;
    if(u_grass_flower == 1.0)
        result_1 = texColor * v_pointcolor + vec4(0.15,-0.05,0.01,1.0) * u_red + vec4(0.15,0.05,0.25,1.0) * u_white;
    else
        result_1 = texColor;
//归一法线方向：
    vec3 nor = normalize(v_normal);
//计算平行光路径：
    vec3 LightDir = normalize(vec3(0.0 , -120.0 , 0.0)-u_light.position);
//设置环境光：
    vec3 environment = vec3(0.3) * u_light.color;
//计算漫反射：
    float diff = max(dot(-LightDir , nor) , 0.0);
    vec3 diffuse = u_strength_light * diff * u_light.color;
//计算阴影：
    float bias = max(0.0035 * (1.0 - dot(nor , LightDir)), 0.0005);
    float shadow = ShadowCaculation(v_Fragpos_LightSpace , bias);

    vec4 result_2 = vec4(environment + (1.0 - shadow) * diffuse , 1.0);
    color = result_1 * result_2;
}