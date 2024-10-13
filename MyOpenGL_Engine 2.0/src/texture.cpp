#include"texture.h"

texture::texture(const std::string& filepath, const bool x)
	:m_data(nullptr),m_texture(0)
{
	stbi_set_flip_vertically_on_load(1);//����opengl�Ǵ�ͼ�ε����½�(0,0)��ʼ�滭����������ṩ�Ĳ��ʷ����Ǵ��ϵ��£��Ǿ�Ҫ�������������������µߵ�
	
	int width, height, BPP;
	m_data = stbi_load(filepath.c_str(), &width, &height, &BPP, 0);//�������

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	if (x == true)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

	stbi_image_free(m_data);
	glBindTexture(GL_TEXTURE_2D, m_texture);

}

texture::~texture()
{
	glDeleteTextures(1, &m_texture);
}

void texture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
