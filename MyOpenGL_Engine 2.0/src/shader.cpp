#include<GL/glew.h>
#include"shader.h"
#include"extra/glm/gtc/type_ptr.hpp"

Shader::Shader(bool geometryOption ,const std::string& pathfile)
	:m_shaderID(0),m_geomtery_Option(geometryOption)
{
	ShaderFileType src = GetShaderFile(pathfile);
	m_filepath << pathfile;
	std::cout << "=========================================================================" << std::endl;
	std::cout << "Outside ShaderContext path: " << pathfile << "\nGeometryShaderMode: ";
	m_geomtery_Option == true ? std::cout << "ON" << std::endl : std::cout << "OFF" << std::endl;
	std::cout << src.VertexShader;
	std::cout << src.GeomteryShader;
	std::cout << src.FragmentShader << "\n=========================================================================" << std::endl;
	m_shaderID = CreatShaderProgram(src.VertexShader, src.FragmentShader, src.GeomteryShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderID);
}

void Shader::InsideShader(const std::string& vertex, const std::string& fragment)
{
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cout << "Inside ShaderContext: " << std::endl;
	std::cout << vertex << std::endl;
	std::cout << fragment << std::endl;
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::string empty = "";
	m_shaderID = CreatShaderProgram(vertex, fragment, empty);
}

void Shader::InsideShader(const std::string& vertex, const std::string& fragment, const std::string& geometry)
{
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cout << "Inside ShaderContext: " << std::endl;
	std::cout << vertex << std::endl;
	std::cout << geometry << std::endl;
	std::cout << fragment << std::endl;
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	m_shaderID = CreatShaderProgram(vertex, fragment, geometry);
}

void Shader::bind()
{
	glUseProgram(m_shaderID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setuniformMat4f(const std::string& name, const glm::mat4& maritx)
{
	glUniformMatrix4fv(setuniformname(name), 1, GL_FALSE, glm::value_ptr(maritx));
}

void Shader::setuniformMat4fv(const std::string& name, const int count, glm::mat4* martix)
{
	std::stringstream ss;
	for (int i = 0; i < count; i++)
	{
		ss.str("");
		ss << name << "[" << i << "]";
		glUniformMatrix4fv(setuniformname(ss.str()), 1, GL_FALSE, glm::value_ptr(martix[i]));
	}
}

void Shader::setuniform1i(const std::string& name, const int i1)
{
	glUniform1i(setuniformname(name), i1);
}

void Shader::setuniform1iv(const std::string& name, const int count, int* array)
{
	glUniform1iv(setuniformname(name), count, array);
}

void Shader::setuniform1f(const std::string& name, const float f1)
{
	glUniform1f(setuniformname(name),f1);
}

void Shader::setuniformVEC2(const std::string& name, const float f1, const float f2)
{
	glUniform2f(setuniformname(name), f1, f2);
}

void Shader::setuniformVEC3(const std::string& name, const float f1, const float f2, const float f3)
{
	glUniform3f(setuniformname(name), f1, f2, f3);
}

void Shader::setuniformVEC4(const std::string& name, const float f1, const float f2, const float f3, const float f4)
{
	glUniform4f(setuniformname(name), f1, f2, f3, f4);
}

ShaderFileType Shader::GetShaderFile(const std::string& pathfile)
{
	std::string line;
	std::fstream stream(pathfile);
	std::stringstream ss[3];
	int type = -1;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex")!= std::string::npos)
				type = 0;
			else if (line.find("fragment") != std::string::npos)
				type = 1;
			else if (line.find("geometry") != std::string::npos)
				type = 2;
		}
		else
			ss[type] << line << "\n";
		
	};
	return { ss[0].str(), ss[1].str(), ss[2].str() };
}

unsigned int Shader::CreatShader(unsigned int type, const std::string& shaderfile)
{
	unsigned int id = glCreateShader(type);
	const char* src = shaderfile.c_str();
	glShaderSource(id,1,&src,nullptr);
	glCompileShader(id);
	int checker;
	glGetShaderiv(id, GL_COMPILE_STATUS, &checker);
//报错输出日志:
	if (checker == GL_FALSE)
	{
		system("color 04");
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* errorMessage = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errorMessage);
		printf("\n[Shader Error!]:");
		if (type == GL_VERTEX_SHADER)
			printf("(VertexShader)\n");
		else if (type == GL_FRAGMENT_SHADER)
			printf("(FragmenShader)\n");
		else if (type == GL_GEOMETRY_SHADER)
			printf("(GeometryShader)\n");
		printf("ErrorLog:\n%s\n", errorMessage);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreatShaderProgram(const std::string& vertex, const std::string& fragment, const std::string& geometry)
{
	unsigned int program = glCreateProgram();
	unsigned int vsh = CreatShader(GL_VERTEX_SHADER, vertex);
	unsigned int fsh = CreatShader(GL_FRAGMENT_SHADER, fragment);
	unsigned int gsh = CreatShader(GL_GEOMETRY_SHADER, geometry);
	glAttachShader(program, vsh);
	if (m_geomtery_Option == true)
		glAttachShader(program, gsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vsh);
	glDeleteShader(fsh);
	glDeleteShader(gsh);
	return program;
}

int Shader::setuniformname(const std::string& name)
{
	if (m_uniform_locationCache.find(name) != m_uniform_locationCache.end())
		return m_uniform_locationCache[name];
	int location = glGetUniformLocation(m_shaderID, name.c_str());
	if (location == -1)
	{
		system("color 06");
		std::cout << "文件地址：" << m_filepath.str() << "\n[设置统一变量警告]" << name << "此变量可能未创建或未使用！" << std::endl;
	}
	m_uniform_locationCache[name] = location;
	return location;
}
