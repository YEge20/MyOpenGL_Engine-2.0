#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 A_normal;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_rota;

out vec3 v_texcoord;
out vec3 v_nor;
out vec3 v_Fragpos;
void main()
{
    gl_Position = u_MVP * position;
    v_texcoord = vec3(position);
    v_nor = vec3(u_rota * vec4(A_normal , 1.0));//�����ת���ܺ���ҲҪ��ת
    v_Fragpos = vec3(u_model * position);//��ÿ�����㶼��������������
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//���ù�Դ����
struct Light{
    vec3 diraction;
    vec3 color;
};

uniform Light u_light;
uniform samplerCube u_sampler0;
uniform vec3 u_fire;
uniform vec3 u_view_position;

in vec3 v_texcoord;
in vec3 v_nor;
in vec3 v_Fragpos;
void main()
{   
//��һ�����߷���
    vec3 nor = normalize(v_nor);
//������·����
    vec3 LightDir = normalize(-u_light.diraction);
//���������䣺
    float diff = max(dot(-LightDir , nor),0.0);
    vec3 diffuse = diff * u_light.color;
//���㾵�淴�䣺
    vec3 view_diract = normalize(u_view_position - v_Fragpos);
    vec3 refl_light_diract = reflect(LightDir , nor);
    float spec = pow(max(dot(view_diract , refl_light_diract) , 0.0),32);
    vec3 specular = spec * u_light.color;
//��ԴЧ�������
    vec3 result = diffuse + specular;
    color = texture(u_sampler0,v_texcoord) * (vec4(u_fire,1.0) + vec4(result,1.0));
}