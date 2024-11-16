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
    Fragpos = vec3(u_copy * u_model * position);//�Ѷ���ȫ����ת������������
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_view_position;// �۲��ߵ�λ��

in vec2 texture_color;
in vec3 normal;
in vec3 Fragpos;

//���ò��ϲ�ͬ��ʽ���������
struct Metrial{
    sampler2D diffuse;//�������������������
    sampler2D specular;//���淴�����ɫ
    float shinness;//���淴���ɢ��뾶
};
uniform Metrial u_material;
//���ù�Դ������
struct Light{
    vec3 position;//��Դ��λ��
    vec3 ambientcolor;//�������������ɫ,һ��Ҫ��
    vec3 diffuse;//��������������ɫ,ע�ⲻҪ̫��
    vec3 specular;//�������淴�����ɫ,��һ��
};
#define PointLight 6
uniform Light u_light[PointLight];
//�����ֵ�Ͳ������
struct FlashLight{
    vec3 position;//�ֵ�Ͳ��λ��
    vec3 diract;//�ֵ�Ͳ�ķ���
    float cutoff;//����������ģ����Ե���Ҽн�
    float OutCutoff;//������������Ҽн�
    int flashSwitch;//�ֵ�Ͳ�Ŀ���
};
uniform FlashLight u_flash;
//���ù��ߵľ���˥������
struct LightAttenuatuon{
    float C;//���ù��߾���˥������
    float L;//���ù��߾���˥��һ����ϵ��
    float Q;//���ù��߾���˥��������ϵ��
};
uniform LightAttenuatuon u_PLight_ATT;//���Դ�ľ���˥��
uniform LightAttenuatuon u_FLight_ATT;//�ֵ�Ͳ�ľ���˥��

//���Դ���㺯��
vec3 LightFun(Light light , vec3 view_position)
{
//���Դ����˥������
    float distance = length(light.position - Fragpos);
    float attenuation = 1.0 / (u_PLight_ATT.C + u_PLight_ATT.L * distance + u_PLight_ATT.Q * pow(distance , 2.0));
//���㻷����
    vec3 environment = light.ambientcolor * vec3(texture(u_material.diffuse , texture_color));
//�����������
    vec3 nor = normalize(normal);
    vec3 light_diract = normalize(light.position - Fragpos);
    float diff1 = max(dot(nor , light_diract),0.0);
    vec3 diffuse = light.diffuse * diff1 * vec3(texture(u_material.diffuse , texture_color));
//���㾵�淴��߹�
    vec3 view_diract = normalize(view_position - Fragpos);
    vec3 HDir = normalize(view_diract + light_diract);
    float spec =  pow(max(dot(nor , HDir),0.0),u_material.shinness);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular,texture_color));
//�������Ч��
    vec3 result = (diffuse + environment + specular) * attenuation;
    return result;
};

//�ֵ�Ͳ���㺯��
vec3 FlashFun(FlashLight flash)
{
//�ֵ�Ͳ����˥������
    float distance = length(flash.position - Fragpos);
    float attenuation = 1.0 / (u_FLight_ATT.C + u_FLight_ATT.L * distance + u_FLight_ATT.Q * pow(distance , 2.0));
//�����ֵ�Ͳ�Ĺ���
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