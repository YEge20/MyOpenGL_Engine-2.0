#include"DepthMapBuffer.h"

DepthMapBuffer::DepthMapBuffer(int size)
	:m_depthMap(0),m_FBO(0)
{
	glGenFramebuffers(1, &m_FBO);

	const int SHADOW_WIDTH = size, SHADOW_HEIGHT = size;
	glGenTextures(1, &m_depthMap);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

DepthMapBuffer::~DepthMapBuffer()
{
}

unsigned int DepthMapBuffer::FBOid()
{
	return m_FBO;
}

void DepthMapBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void DepthMapBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthMapBuffer::use(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
}
