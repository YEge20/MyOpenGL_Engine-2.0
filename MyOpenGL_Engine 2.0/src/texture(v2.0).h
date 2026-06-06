#pragma once
#include <string>


class Texture_2D
{
public:
	Texture_2D(const std::string& pathfile, const bool LinearSetup = true);
	~Texture_2D();

	void Bind(unsigned int slot);
	void UnBind();

	unsigned int m_Texture;
private:
	std::string m_pathfile;
};