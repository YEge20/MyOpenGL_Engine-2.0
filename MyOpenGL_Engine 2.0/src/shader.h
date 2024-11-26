#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<Windows.h>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include"glm/glm.hpp"
#include<unordered_map>

struct ShaderFileType
{
	std::string VertexShader;
	std::string FragmentShader;
};
class Shader
{
public:
	//��ʼ���ⲿ����ɫ���ļ�(�������գ�Ȼ��ʹ��InsideShader()�����������õ���ɫ������)��
	Shader(const std::string& pathfile);
	~Shader();

	//�����ڳ����ڼ���������ɫ�����ݣ�
	void InsideShader(const std::string& vertex, const std::string& fragment);

	void bind();
	void unbind();

	//����ͳһ������
	void setuniformMat4f(const std::string& name, const glm::mat4& maritx);//4*4����
	void setuniform1i(const std::string& name, const int i1);//����1������
	void setuniform1iv(const std::string& name, const int count, int* array);//����1����������
	void setuniform1f(const std::string& name, const float f1);
	void setuniformVEC2(const std::string& name, const float f1, const float f2);
	void setuniformVEC3(const std::string& name, const float f1, const float f2, const float f3);
	void setuniformVEC4(const std::string& name, const float f1, const float f2, const float f3, const float f4);

private:
	ShaderFileType GetShaderFile(const std::string& pathfile);
	unsigned int CreatShader(unsigned int type, const std::string& shaderfile);
	int setuniformname(const std::string& name);
	unsigned int CreatShaderProgram(const std::string& vertex, const std::string& fragment);
	unsigned int m_shaderID;
	std::unordered_map<std::string, int> m_uniform_locationCache;
	std::stringstream m_filepath;
};
