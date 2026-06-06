#pragma once
#include <string>

class texture
{
public:
	texture(const std::string& filepath, const bool LINEAR_MODE);
	~texture();

	void bind(unsigned int slot);
	void unbind();

	int GetChannel() { return m_channel; }
	unsigned int GetTextureID() { return m_texture; }

private:
	unsigned int m_texture;
	unsigned char* m_data;
	int m_channel;
};