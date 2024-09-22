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
//此api允许同时一次性绑定10个shader文件
//注意：该API与texture32API有冲突，如果先调用了texture32的bind功能，则该API的bind功能失效
class ShaderGroup_10_unity
{
public:
	ShaderGroup_10_unity();
	~ShaderGroup_10_unity();
	//导入文件，slot的范围为0~9
	void importshader(const std::string& pathfile, int slot);
	//绑定对应的shader，slot的范围为0~9
	void bind(int slot);
	void unbind();

	//设置统一变量：
	void setuniformMat4f(const std::string& name, const glm::mat4& maritx);//2*2矩阵
	void setuniform1i(const std::string& name, const int i1);//设置1个整数
	void setuniform1iv(const std::string& name, const int count, int* array);//设置1个整数数组
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