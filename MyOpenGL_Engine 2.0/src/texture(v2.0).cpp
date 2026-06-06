#include<GL/glew.h>
#include<stb_image/stb_image.h>
#include"texture(v2.0).h"
#include<iostream>
Texture_2D::Texture_2D(const std::string& pathfile, const bool LinearSetup)
	:m_pathfile(pathfile),m_Texture(0)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);//由于opengl是从图形的左下角(0,0)开始绘画，如果我们提供的材质方向是从上到下，那就要先用这个函数令材质上下颠倒
	stbi_uc* data = stbi_load(m_pathfile.c_str(), &width, &height, &channels, 0);
	if (!data)
		std::cout << "failed to files!" << std::endl;
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
	if (channels == 3)
		glTextureStorage2D(m_Texture, 1, GL_RGB8, width, height);
	else if (channels == 4)
		glTextureStorage2D(m_Texture, 1, GL_RGBA8, width, height);
	if (LinearSetup == false)
	{
		glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (channels == 3)
		glTextureSubImage2D(m_Texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if(channels == 4)
		glTextureSubImage2D(m_Texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}

Texture_2D::~Texture_2D()
{
	glDeleteTextures(1, &m_Texture);
}

void Texture_2D::Bind(unsigned int slot)
{
	glBindTextureUnit(slot, m_Texture);
}

void Texture_2D::UnBind()
{
	glBindTextureUnit(0, 0);
}
