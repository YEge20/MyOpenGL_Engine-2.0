#pragma once
#include<iostream>
#include<Windows.h>
#include<gl/glew.h>
#include<memory>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
//��������֡���巽������������ĳ�������������ͼ
enum Param
{
	LINEAR_MODE = 0, NEARLIST_MODE
};

class DynamicEnvironmentBuffer
{
public:
	//��ʼ����size������ͼ�ķֱ��ʣ�param��������ͼ�Ĺ���ģʽ
	DynamicEnvironmentBuffer(int size, Param param = LINEAR_MODE);
	~DynamicEnvironmentBuffer();

	//��Ҫ��ʼ���ɵĳ���ǰ��,��ı��ӿڵĴ�С
	void Bind();

	////ʹ�ø�API�Ƽ��������ṩ���Զ���������Ҫ����ͼ������������////
	/*��������������ͼ��widthΪ��Ⱦ����Ŀ�ȣ�heightΪ��Ⱦ����߶�,farplaneΪ�ܿ�����Զ�ľ���*/
	glm::mat4 Caculate_Ortho_Project(float width, float height, float farplane);
	/*����͸�Ӿ���fov_angleΪ�ӽǼнǣ���λ�Ƕȣ�width����Ⱦ����Ŀ�ȣ�heightΪ��Ⱦ����߶�,farplaneΪ�ܿ�����Զ�ľ���*/
	glm::mat4 Caculate_Perspective_Project(float fov_angle, float width, float height, float farplane);
	/*�����������Cam_Pos�ǹ۲�ʱ��λ�ã�Cam_Fro�ǹ۲�ķ������緽��������x����������ǾͿ�����������glm::vec3(1.0f,0.0f,0.0f)��*/
	glm::mat4 Caculate_Camera(glm::vec3 Cam_Pos, glm::vec3 Cam_Fro);

	//������Ⱦ�������ʹ�ý�󲢻ָ���������Ⱦ�����ֶ�����glviewport()�ֶ���ԭ��ԭ�����ӿڴ�С��
	void UnBind();
	//�󶨵�����ʹ�ö�Ӧ��GL_TEXTURE�����ȥ
	void setGLTextureSlot(int GL_Texture_slot);

	////���µ����������ṩ������Ķ�̬������ͼ�����ӣ�ʹ��˳������////
	/*�ȳ�ʼ����ɫ����ִֻ��һ�Σ���*/
	void TestShader();
	/*Ȼ�����ɫ������ѭ����ִ�У���*/
	void TestShaderBind();
	/*�������MVP����ѭ���и��£���*/
	void SetTestShaderMVP(glm::mat4 MVP);
private:
	unsigned int m_FBO;
	unsigned int m_DynamicEnvironmentTexture;
	unsigned int m_RBO;
	int m_width, m_height;
	Param m_param;//��ͼ�Ĺ���ģʽ
	std::shared_ptr<Shader> m_test_shader;
	bool m_shader_intalize = false;
};