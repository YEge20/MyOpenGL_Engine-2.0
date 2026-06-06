#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<Windows.h>
#include <GLFW/glfw3.h>
#include"glm/glm.hpp"
#include<unordered_map>

struct ShaderFileType
{
	std::string VertexShader;
	std::string FragmentShader;
	std::string GeomteryShader;
};
class Shader
{
public:
	//初始化外部的着色器文件(pathfile可以留空，然后使用InsideShader()函数加载内置的着色器内容)
	//参数：geometryOption为是否加载几何着色器true为启用，pathfile为你的文件相对于该项目的地址
	Shader(bool geometryOption ,const std::string& pathfile);
	~Shader();

	unsigned int GetProgram()const { return m_shaderID; }

	//允许在程序内加载内置着色器内容：
	void InsideShader(const std::string& vertex, const std::string& fragment);
	void InsideShader(const std::string& vertex, const std::string& fragment, const std::string& geometry);

	void bind();
	void unbind();

	//设置统一变量：
	void setuniformMat4f(const std::string& name, const glm::mat4& maritx);//4*4矩阵
	void setuniformMat4fv(const std::string& name, const int count, glm::mat4* martix);//设置4*4的矩阵数组
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
	unsigned int CreatShaderProgram(const std::string& vertex, const std::string& fragment, const std::string& geometry);
	unsigned int m_shaderID;
	std::unordered_map<std::string, int> m_uniform_locationCache;
	std::stringstream m_filepath;
	bool m_geomtery_Option;
};
