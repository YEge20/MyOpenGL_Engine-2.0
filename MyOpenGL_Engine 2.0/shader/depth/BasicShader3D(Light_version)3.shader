#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 A_normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_rota;
uniform mat4 u_LightMartix;

out vec2 v_texcoord;
out vec3 v_nor;
out vec3 v_Fragpos;
out vec3 v_texcoord_cube;
out vec4 v_Fragpos_LightSpace;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = texcoord;
    v_nor = vec3(u_rota * vec4(A_normal , 1.0));//添加旋转功能后法线也要旋转
    v_Fragpos = vec3(u_model * position);//让每个顶点都落在世界坐标上
    v_texcoord_cube = vec3(position);
    v_Fragpos_LightSpace = u_LightMartix * vec4(v_Fragpos , 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//设置光源属性
struct Light{
    vec3 position;
    vec3 color;
};

uniform Light u_light;
uniform sampler2D u_sampler;
uniform sampler2D u_sampler_light_ore_pbr;
uniform sampler2D u_sampler_reflect_pbr;
uniform float u_render_type;
uniform samplerCube u_sampler_CubeBlock;
uniform sampler2D u_depth_texture;//深度图
uniform vec3 u_view_position;
uniform float u_strength_light;//平行光的强度

in vec2 v_texcoord;
in vec3 v_nor;
in vec3 v_Fragpos;
in vec3 v_texcoord_cube;
in vec4 v_Fragpos_LightSpace;

float ShadowCaculation(vec4 v_Fragpos_LightSpace , float bias)
{
    //执行透视分割并把数值转换成0~1的范围
    vec3 procoord = v_Fragpos_LightSpace.xyz / v_Fragpos_LightSpace.w;
    procoord = procoord * 0.5 + 0.5;
    //获取离光源最近的深度值
    float closestDepth = texture(u_depth_texture , procoord.xy).r;
    //获取当前深度值
    float currentDepth = procoord.z;
    //判断是否出于阴影之中:
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    vec3 LightDir_2 = normalize(u_light.position - vec3(0.0 , -120.0 , 0.0));
    vec3 nor_2 = normalize(v_nor);
    float degree = max(dot(LightDir_2 , nor_2) , 0.0);
    if(degree < 0.0872)
        shadow = 1.0 * (1.0 - 10.0 * degree);
    return shadow;
}

void main()
{   
//归一化法线方向：
    vec3 nor = normalize(v_nor);
//计算平行光的路径：
    vec3 LightDir = normalize(vec3(0.0 , -120.0 , 0.0)-u_light.position);
//设置环境光：
    vec3 environment = vec3(0.3) * u_light.color;
//计算漫反射：
    float diff = max(dot(-LightDir , nor),0.0);
    vec3 diffuse = u_strength_light * diff * u_light.color;
//计算镜面反射：
    vec3 view_diract = normalize(u_view_position - v_Fragpos);
    vec3 HDir = normalize(-LightDir + view_diract);
    float spec = pow(max(dot(nor , HDir) , 0.0) , 64);
    vec3 specular = u_strength_light * spec * u_light.color;
//计算阴影：
    float bias = max(0.002 * (1.0 - dot(nor , LightDir)), 0.0005);
    float shadow = ShadowCaculation(v_Fragpos_LightSpace , bias);
//光源效果输出：
    if(u_render_type == 1.0)
        color = texture(u_sampler_CubeBlock , -v_texcoord_cube) * vec4(environment + (1.0 - shadow) * (diffuse + specular), 1.0);
    else
        color = (1.0 - shadow) * texture(u_sampler_reflect_pbr , v_texcoord) * vec4(specular , 1.0) + texture(u_sampler_light_ore_pbr , v_texcoord) * vec4(1.4,1.4,1.4,1.0) + (1.0 - shadow) * texture(u_sampler , v_texcoord) * vec4(diffuse , 1.0) +  + texture(u_sampler , v_texcoord) * vec4(environment , 1.0);
}