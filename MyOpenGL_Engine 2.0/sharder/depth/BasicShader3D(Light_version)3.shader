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
    v_nor = vec3(u_rota * vec4(A_normal , 1.0));//�����ת���ܺ���ҲҪ��ת
    v_Fragpos = vec3(u_model * position);//��ÿ�����㶼��������������
    v_texcoord_cube = vec3(position);
    v_Fragpos_LightSpace = u_LightMartix * vec4(v_Fragpos , 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//���ù�Դ����
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
uniform sampler2D u_depth_texture;//���ͼ
uniform vec3 u_view_position;
uniform float u_strength_light;//ƽ�й��ǿ��

in vec2 v_texcoord;
in vec3 v_nor;
in vec3 v_Fragpos;
in vec3 v_texcoord_cube;
in vec4 v_Fragpos_LightSpace;

float ShadowCaculation(vec4 v_Fragpos_LightSpace , float bias)
{
    //ִ��͸�ӷָ����ֵת����0~1�ķ�Χ
    vec3 procoord = v_Fragpos_LightSpace.xyz / v_Fragpos_LightSpace.w;
    procoord = procoord * 0.5 + 0.5;
    //��ȡ���Դ��������ֵ
    float closestDepth = texture(u_depth_texture , procoord.xy).r;
    //��ȡ��ǰ���ֵ
    float currentDepth = procoord.z;
    //�ж��Ƿ������Ӱ֮��:
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
//��һ�����߷���
    vec3 nor = normalize(v_nor);
//����ƽ�й��·����
    vec3 LightDir = normalize(vec3(0.0 , -120.0 , 0.0)-u_light.position);
//���û����⣺
    vec3 environment = vec3(0.3) * u_light.color;
//���������䣺
    float diff = max(dot(-LightDir , nor),0.0);
    vec3 diffuse = u_strength_light * diff * u_light.color;
//���㾵�淴�䣺
    vec3 view_diract = normalize(u_view_position - v_Fragpos);
    vec3 HDir = normalize(-LightDir + view_diract);
    float spec = pow(max(dot(nor , HDir) , 0.0) , 64);
    vec3 specular = u_strength_light * spec * u_light.color;
//������Ӱ��
    float bias = max(0.002 * (1.0 - dot(nor , LightDir)), 0.0005);
    float shadow = ShadowCaculation(v_Fragpos_LightSpace , bias);
//��ԴЧ�������
    if(u_render_type == 1.0)
        color = texture(u_sampler_CubeBlock , -v_texcoord_cube) * vec4(environment + (1.0 - shadow) * (diffuse + specular), 1.0);
    else
        color = (1.0 - shadow) * texture(u_sampler_reflect_pbr , v_texcoord) * vec4(specular , 1.0) + texture(u_sampler_light_ore_pbr , v_texcoord) * vec4(1.4,1.4,1.4,1.0) + (1.0 - shadow) * texture(u_sampler , v_texcoord) * vec4(diffuse , 1.0) +  + texture(u_sampler , v_texcoord) * vec4(environment , 1.0);
}