#include"TextureBlock8.h"

TextureBlock8::TextureBlock8(bool LINEARmode)
	:m_texture{0}, m_data(nullptr)
{	
	glGenTextures(8, m_texture);
	m_LINEAR = LINEARmode;
}

TextureBlock8::~TextureBlock8()
{
	glDeleteTextures(8, m_texture);
}

void TextureBlock8::importtexture(std::vector<std::string> face, int slot)
{	
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture[slot]);
	int width, height, BPP;
	for (int i = 0; i < face.size(); i++)
	{
		m_data = stbi_load(face[i].c_str(), &width, &height, &BPP, 0);
		if (BPP == 4)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		else if(BPP == 3)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		stbi_image_free(m_data);
	}

	if (m_LINEAR == true)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureBlock8::bind(int slot)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture[slot]);
}

void TextureBlock8::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
