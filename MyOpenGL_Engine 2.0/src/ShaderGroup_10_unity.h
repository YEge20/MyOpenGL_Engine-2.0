#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include"glm/glm.hpp"
#include<unordered_map>

struct ShaderGroupFileType
{
	std::string VertexShader;
	std::string FragmentShader;
};
//��api����ͬʱһ���԰�10��shader�ļ�
//ע�⣺��API��texture32API�г�ͻ������ȵ�����texture32��bind���ܣ����API��bind����ʧЧ
class ShaderGroup_10_unity
{
public:
	ShaderGroup_10_unity();
	~ShaderGroup_10_unity();
	//�����ļ���slot�ķ�ΧΪ0~9
	void importshader(const std::string& pathfile, int slot);
	//�󶨶�Ӧ��shader��slot�ķ�ΧΪ0~9
	void bind(int slot);
	void unbind();

	//����ͳһ������
	void setuniformMat4f(const std::string& name, const glm::mat4& maritx);//2*2����
	void setuniform1i(const std::string& name, const int i1);//����1������
	void setuniform1iv(const std::string& name, const int count, int* array);//����1����������
	void setuniform1f(const std::string& name, const float f1);
	void setuniformVEC2(const std::string& name, const float f1, const float f2);
	void setuniformVEC3(const std::string& name, const float f1, const float f2, const float f3);
	void setuniformVEC4(const std::string& name, const float f1, const float f2, const float f3, const float f4);

private:
	ShaderGroupFileType GetShaderFile(const std::string& pathfile);
	unsigned int CreatShader(unsigned int type, const std::string& shaderfile);
	unsigned int CreatShaderProgram(const std::string& vertex, const std::string& fragment);
	int setuniformname(const std::string& name);
	unsigned int m_shaderID[10], m_shaderID_current;
	std::unordered_map<std::string, int> m_uniform_locationCache;
	std::stringstream m_filepath;
};