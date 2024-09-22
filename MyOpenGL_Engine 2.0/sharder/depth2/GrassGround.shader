#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcood;
layout(location = 2) in vec4 VerColor;
layout(location = 3) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_LightMartix;

out vec4 v_VerColor;
out vec2 v_texcood;
out vec3 v_Fragpos;
out vec3 v_normal;
out vec4 v_Fragpos_LightSpace;
void main()
{
    gl_Position = u_MVP * position;
    v_VerColor = VerColor;

    v_Fragpos = vec3(u_model * position);//��ÿ�����㶼��������������
    v_texcood = texcood;
    v_normal = normal;
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
uniform vec3 u_view_position;
uniform sampler2D u_texture0;//�ݲ�����ͼ
uniform sampler2D u_texture1;//����������ͼ
uniform sampler2D u_texture2;//�����ͼ
uniform float u_red;
uniform float u_white;
uniform float u_strength_light;//ƽ�й��ǿ��


in vec4 v_VerColor;
in vec2 v_texcood;
in vec3 v_Fragpos;
in vec3 v_normal;
in vec4 v_Fragpos_LightSpace;

float LinearizeDepth(float DepthValue)
{
    float z = DepthValue * 0.5 + 0.5;
    return z;
}

float ShadowCaculation(vec4 v_Fragpos_LightSpace , float bias)
{
    //ִ��͸�ӷָ����ֵת����0~1�ķ�Χ
    vec3 procoord = v_Fragpos_LightSpace.xyz / v_Fragpos_LightSpace.w;
    procoord = procoord * 0.5 + 0.5;
    //��ȡ���Դ��������ֵ
    float closestDepth = LinearizeDepth(texture(u_texture2 , procoord.xy).r);
    //��ȡ��ǰ���ֵ
    float currentDepth = LinearizeDepth(procoord.z);
    //�ж��Ƿ������Ӱ֮�У�    
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    vec3 LightDir_2 = normalize(u_light.position - vec3(0.0 , -120.0 , 0.0));
    vec3 nor_2 = normalize(v_normal);
    float degree = max(dot(LightDir_2 , nor_2) , 0.0);
    if(degree < 0.087)
        shadow = 1.0 * (1.0 - 10.0 * degree);
    
    return shadow;
}

void main()
{   
//��һ���߷���
    vec3 nor = normalize(v_normal);
//����ƽ�й�·����
    vec3 LightDir = normalize(vec3(0.0 , -120.0 , 0.0) - u_light.position);
//���û����⣺
    vec3 environment = vec3(0.3) * u_light.color;
//���������䣺
    float diff = max(dot(-LightDir , nor) , 0.0);
    vec3 diffuse = u_strength_light * diff * u_light.color;
//���㾵�淴�䣺
    vec3 view_diract = normalize(u_view_position - v_Fragpos);
    vec3 HDir = normalize(-LightDir + view_diract);
    float spec = pow(max(dot(nor , HDir) , 0.0) , 8);
    vec3 specular = u_strength_light * spec * u_light.color;
//�ݵصĲ��ʼ���
    vec4 Fragcolor = mix(texture(u_texture0 , v_texcood) , texture(u_texture1 , v_texcood) , 0.2 + 0.5 * u_white) + v_VerColor * u_red;
//��Ӱ����
    float bias = max(0.0025 * (1.0 - dot(nor , LightDir)) , 0.0005);
    float shadow = ShadowCaculation(v_Fragpos_LightSpace , bias);

    vec4 resultLight = vec4(environment +  (1.0 - shadow) * (diffuse + specular) , 1.0);
    color = Fragcolor * resultLight;
}