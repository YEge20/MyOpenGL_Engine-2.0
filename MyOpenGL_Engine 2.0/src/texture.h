#pragma once
#include "stb_image/stb_image.h"
#include <string>
#include"GL/glew.h"

class texture
{
public:
	texture(const std::string& filepath, const bool LINEAR_MODE);
	~texture();

	void bind(unsigned int slot);
	void unbind();

	inline int GetChannel() { return m_channel; }
private:
	unsigned int m_texture;
	unsigned char* m_data;
	int m_channel;
};