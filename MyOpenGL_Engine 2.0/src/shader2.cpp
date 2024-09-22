#include"shader2.h"

Shader2::Shader2(const std::string& pathfile)
	:m_shaderID(0)
{
	ShaderFileType2 src = GetShaderFile(pathfile);
	m_filepath << pathfile;
	std::cout << "=========================================================================" << std::endl;
	std::cout << "ShaderContext: " << pathfile << std::endl;
	std::cout << src.VertexShader;
	std::cout << src.FragmentShader << "\n=========================================================================" << std::endl;
	m_shaderID = CreatShaderProgram(src.VertexShader, src.FragmentShader);
}

Shader2::~Shader2()
{
	glDeleteProgram(m_shaderID);
}

void Shader2::bind()
{
	glUseProgram(m_shaderID);
}

void Shader2::unbind()
{
	glUseProgram(0);
}

void Shader2::setuniformMat4f(const std::string& name, const glm::mat4& maritx)
{
	glUniformMatrix4fv(setuniformname(name), 1, GL_FALSE, &maritx[0][0]);
}

void Shader2::setuniform1i(const std::string& name, const int i1)
{
	glUniform1i(setuniformname(name), i1);
}

void Shader2::setuniform1iv(const std::string& name, const int count, int* array)
{
	glUniform1iv(setuniformname(name), count, array);
}

void Shader2::setuniform1f(const std::string& name, const float f1)
{
	glUniform1f(setuniformname(name), f1);
}

void Shader2::setuniformVEC2(const std::string& name, const float f1, const float f2)
{
	glUniform2f(setuniformname(name), f1, f2);
}

void Shader2::setuniformVEC3(const std::string& name, const float f1, const float f2, const float f3)
{
	glUniform3f(setuniformname(name), f1, f2, f3);
}

void Shader2::setuniformVEC4(const std::string& name, const float f1, const float f2, const float f3, const float f4)
{
	glUniform4f(setuniformname(name), f1, f2, f3, f4);
}

ShaderFileType2 Shader2::GetShaderFile(const std::string& pathfile)
{
	std::string line;
	std::fstream stream(pathfile);
	std::stringstream ss[2];
	int type = -1;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = 0;
			else if (line.find("fragment") != std::string::npos)
				type = 1;
		}
		else
			ss[type] << line << "\n";

	};
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader2::CreatShader(unsigned int type, const std::string& shaderfile)
{
	unsigned int id = glCreateShader(type);
	const char* src = shaderfile.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int checker;
	glGetShaderiv(id, GL_COMPILE_STATUS, &checker);
	//报错输出日志:
	if (checker == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* errorMessage = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errorMessage);
		printf("\n[Shader Error!]:");
		if (type == GL_VERTEX_SHADER)
			printf("(Vertexshader)\n");
		else
			printf("(Fragmenshader)\n");
		printf("ErrorLog:\n%s\n", errorMessage);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader2::CreatShaderProgram(const std::string& vertex, const std::string& fragment)
{
	unsigned int program = glCreateProgram();
	unsigned int vsh = CreatShader(GL_VERTEX_SHADER, vertex);
	unsigned int fsh = CreatShader(GL_FRAGMENT_SHADER, fragment);
	glAttachShader(program, vsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vsh);
	glDeleteShader(fsh);
	return program;
}

int Shader2::setuniformname(const std::string& name)
{
	if (m_uniform_locationCache.find(name) != m_uniform_locationCache.end())
		return m_uniform_locationCache[name];
	int location = glGetUniformLocation(m_shaderID, name.c_str());
	if (location == -1)
		std::cout << "文件地址：" << m_filepath.str() << "\n[设置统一变量错误]" << name << "此变量可能未创建或未使用！" << std::endl;
	m_uniform_locationCache[name] = location;
	return location;
}
