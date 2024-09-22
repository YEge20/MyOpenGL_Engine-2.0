#pragma once
#include "stb_image/stb_image.h"
#include <string>
#include"GL/glew.h"

class texture
{
public:
	texture(const std::string& filepath, const bool x);
	~texture();

	void bind(unsigned int slot);
	void unbind();
private:
	unsigned int m_texture;
	unsigned char* m_data;
};