#include "DynamicEnvironmentBuffer.h"

DynamicEnvironmentBuffer::DynamicEnvironmentBuffer(int size, Param param)
	:m_FBO(0),m_DynamicEnvironmentTexture(0),m_RBO(0),m_param(param)
{
	m_width = size;
	m_height = size;
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glGenTextures(1, &m_DynamicEnvironmentTexture);
	glBindTexture(GL_TEXTURE_2D, m_DynamicEnvironmentTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	if (m_param == LINEAR_MODE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (m_param == NEARLIST_MODE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_DynamicEnvironmentTexture, 0);

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

DynamicEnvironmentBuffer::~DynamicEnvironmentBuffer()
{
	glDeleteFramebuffers(1, &m_FBO);
}

void DynamicEnvironmentBuffer::setGLTextureSlot(int GL_Texture_slot)
{
	glActiveTexture(GL_TEXTURE0 + GL_Texture_slot);
	glBindTexture(GL_TEXTURE_2D, m_DynamicEnvironmentTexture);
}

void DynamicEnvironmentBuffer::TestShader()
{
	ShaderFileType src;
	src.VertexShader = R"(
	#version 330 core

	layout(location = 0) in vec4 position;
	layout(location = 1) in vec2 uv;

	uniform mat4 u_MVP;

	out vec2 texcoord;
	void main()
	{
		texcoord = uv;
		gl_Position = u_MVP * position;
	}
	)";
	src.FragmentShader = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform sampler2D u_texture;

	in vec2 texcoord;
	void main()
	{
		color = texture(u_texture, texcoord);
	}
	)";
	if (m_shader_intalize == false)
	{
		m_test_shader.reset(new Shader(""));
		m_test_shader->InsideShader(src.VertexShader, src.FragmentShader);
	}
}

void DynamicEnvironmentBuffer::TestShaderBind()
{
	m_test_shader->bind();
}

void DynamicEnvironmentBuffer::SetTestShaderMVP(glm::mat4 MVP)
{
	m_test_shader->setuniformMat4f("u_MVP", MVP);
}

void DynamicEnvironmentBuffer::Bind()
{
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	setGLTextureSlot(0);
}

glm::mat4 DynamicEnvironmentBuffer::Caculate_Ortho_Project(float width, float height, float farplane)
{
	float x, y;
	x = width / 2;
	y = height / 2;
	glm::mat4 project = glm::ortho(-x, x, -y, y, 0.1f, farplane);
	return project;
}

glm::mat4 DynamicEnvironmentBuffer::Caculate_Perspective_Project(float fov_angle, float width, float height, float farplane)
{
	glm::mat4 project = glm::perspective(glm::radians(fov_angle), width / height, 0.1f, farplane);
	return project;
}

glm::mat4 DynamicEnvironmentBuffer::Caculate_Camera(glm::vec3 Cam_Pos, glm::vec3 Cam_Fro)
{
	glm::vec3 lookat = Cam_Pos + glm::normalize(Cam_Fro);
	glm::mat4 Camera = glm::lookAt(Cam_Pos, lookat, glm::vec3(0.0f, 1.0f, 0.0f));
	return Camera;
}


void DynamicEnvironmentBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
