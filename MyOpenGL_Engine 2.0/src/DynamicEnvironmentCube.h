#pragma once
#include<gl/glew.h>
#include"shader.h"
#include<memory>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

class DynamicEnvironmentCube
{
public:
	//sizeΪ�ֱ��ʣ�parmaΪ���ˣ�true��ʹ��GL_LINEAR��false��ʹ��GL_NEAREST��positionΪ��̬�����ļ�����������
	DynamicEnvironmentCube(int size, bool parma, glm::vec3 position);
	~DynamicEnvironmentCube();

	//��Ⱦ��˳����(face:0)->��(face:1)->��(face:2)->��(face:3)->ǰ(face:4)->��(face:5),diract��face��ֵһ��
	void bind(int face);

	//////��Ⱦ����ͼʱ�����ʹ�������������������Ⱦ���ſ���ʹ�õ�������ͼ��������ȷ//////
	/*�����������diractΪ6�����Ӧ�ķ���*/
	glm::mat4 Dynamic_Cam(int diract);
	/*��ͼ������������һ����ȷ��͸�Ӿ���*/
	glm::mat4 Dynamic_Project();

	//������Ⱦ�������ʹ�ý�󲢻ָ���������Ⱦ�����ֶ�����glviewport()�ֶ���ԭ��ԭ�����ӿڴ�С��
	void UnBind();
	//����Ⱦʱ�������:
	void UseDynamicCubeTexture();
	//���ڸı䷴��λ�õ�����:
	inline void Modifie_position(glm::vec3 new_position) { m_position = new_position; };

	////���µ����������ṩ������Ķ�̬������ͼ�����ӣ�ʹ��˳������////
	/*�ȳ�ʼ����ɫ����ִֻ��һ�Σ���*/
	void TestShader();
	/*Ȼ�����ɫ������ѭ����ִ�У���*/
	void TestShaderBind();
	/*�������MVP����ѭ���и��£���*/
	void SetTestShaderMVP(glm::mat4 MVP);
private:
	unsigned int m_texture = 0, m_FBO = 0, m_RBO = 0;
	int m_width = 0, m_height = 0;
	bool m_param;
	glm::vec3 m_position = { 0.0f,0.0f,0.0f };
	std::shared_ptr<Shader> m_test_shader;//���ò�����ɫ��
	bool m_intalize = false;//�����ɫ���Ƿ��Ѿ����أ�ȷ������ִ�ж�γ�ʼ��
};