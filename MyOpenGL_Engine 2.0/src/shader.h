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
	//初始化外部的着色器文件(可以留空，然后使用InsideShader()函数加载内置的着色器内容)：
	Shader(const std::string& pathfile);
	~Shader();

	//允许在程序内加载内置着色器内容：
	void InsideShader(const std::string& vertex, const std::string& fragment);

	void bind();
	void unbind();

	//设置统一变量：
	void setuniformMat4f(const std::string& name, const glm::mat4& maritx);//4*4矩阵
	void setuniform1i(const std::string& name, const int i1);//设置1个整数
	void setuniform1iv(const std::string& name, const int count, int* array);//设置1个整数数组
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
