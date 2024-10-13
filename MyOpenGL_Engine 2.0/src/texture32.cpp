#include"texture32.h"

texture32::texture32(const bool x)
	:m_data(nullptr),m_texture{0},m_TexParameteri(x)
{
	stbi_set_flip_vertically_on_load(1);//由于opengl是从图形的左下角(0,0)开始绘画，如果我们提供的材质方向是从上到下，那就要先用这个函数令材质上下颠倒
	glGenTextures(32, m_texture);
}

texture32::~texture32()
{
	glDeleteTextures(32, m_texture);
}

void texture32::importTexture(const std::string& filepath, const int position_of_texture)
{
	int width, height, BPP;
	m_data = stbi_load(filepath.c_str(), &width, &height, &BPP, 0);//导入材质
	glBindTexture(GL_TEXTURE_2D, m_texture[position_of_texture]);
	if (m_TexParameteri == true)
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
}

void texture32::bind(unsigned int slot, const int position_of_texture_use)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_texture[position_of_texture_use]);
}

void texture32::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
