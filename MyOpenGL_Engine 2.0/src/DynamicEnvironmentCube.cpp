#include"DynamicEnvironmentCube.h"
#include<iostream>
DynamicEnvironmentCube::DynamicEnvironmentCube(int size, bool parma, glm::vec3 position)
	:m_height(size),m_width(size),m_param(parma),m_position(position)
{
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glGenTextures(1,&m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	for (int x = 0; x < 6; x++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	if(m_param == true)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (m_param == false)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		system("color 06");
		std::cout << "[DynamicEnvironmentBuffer]:Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

DynamicEnvironmentCube::~DynamicEnvironmentCube()
{
	glDeleteRenderbuffers(1, &m_RBO);
	glDeleteFramebuffers(1, &m_FBO);
}

void DynamicEnvironmentCube::bind(int face)
{
	//渲染面顺序：右(0)->左(1)->上(2)->下(3)->前(4)->后(5)
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, m_texture, 0);//把帧缓冲渲染到目标上去
}

glm::mat4 DynamicEnvironmentCube::Dynamic_Cam(int diract)
{
	glm::vec3 front[6] = {
		m_position + glm::vec3(1.0f, 0.0f, 0.0f),
		m_position + glm::vec3(-1.0f, 0.0f, 0.0f),
		m_position + glm::vec3(0.0f, 1.0f, 0.0f),
		m_position + glm::vec3(0.0f,-1.0f, 0.0f),
		m_position + glm::vec3(0.0f, 0.0f, 1.0f),
		m_position + glm::vec3(0.0f, 0.0f,-1.0f)
	};
	glm::vec3 up[6] = {
		{0.0f,-1.0f,0.0f},
		{0.0f,-1.0f,0.0f},
		{0.0f, 0.0f,1.0f},
		{0.0f, 0.0f,-1.0f},
		{0.0f,-1.0f,0.0f},
		{0.0f,-1.0f,0.0f}
	};
	glm::mat4 direct_martix = glm::lookAt(m_position, front[diract], up[diract]);
	return direct_martix;
}

glm::mat4 DynamicEnvironmentCube::Dynamic_Project()
{
	glm::mat4 project = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 800.0f);
	return project;
}

void DynamicEnvironmentCube::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DynamicEnvironmentCube::UseDynamicCubeTexture()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}

void DynamicEnvironmentCube::TestShader()
{	
	ShaderFileType src;
	src.VertexShader = R"(
	#version 330 core

	layout(location = 0) in vec4 position;

	uniform mat4 u_MVP;

	out vec3 texcoord;
	void main()
	{
		texcoord = vec3(position);
		gl_Position = u_MVP * position;
	}
	)";
	src.FragmentShader = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform samplerCube sky;
	in vec3 texcoord;

	void main()
	{
		color = texture(sky, texcoord);
	}
	)";

	if (m_intalize == false)
	{
		m_test_shader.reset(new Shader(""));
		m_test_shader->InsideShader(src.VertexShader, src.FragmentShader);
	}
}

void DynamicEnvironmentCube::SetTestShaderMVP(glm::mat4 MVP)
{
	m_test_shader->setuniformMat4f("u_MVP", MVP);
}

void DynamicEnvironmentCube::TestShaderBind()
{
	m_test_shader->bind();
}
