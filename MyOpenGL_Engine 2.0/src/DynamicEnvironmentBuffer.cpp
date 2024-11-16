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
	if (m_param == NEARLIST_MODE)
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

void DynamicEnvironmentBuffer::Bind()
{
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void DynamicEnvironmentBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
