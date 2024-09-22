#pragma once
#include "stb_image/stb_image.h"
#include<iostream>
#include <string>
#include"GL/glew.h"
#include<vector>
//注意：该API与texture32API有冲突，如果先调用了texture32的bind功能，则该API的bind功能失效
class TextureBlock8
{
public:
	TextureBlock8(bool RGBAmode, bool LINEARmode);//第一个参数为是否使用RGBA存储(默认为RGB),第二个参数为是否使用LINEAR过滤(默认为NEAREST)
	~TextureBlock8();

	void importtexture(std::vector<std::string> face, int slot);
	void bind(int slot);
	void unbind();

private:
	unsigned int m_texture[8];
	unsigned char* m_data;
	bool m_RGB, m_LINEAR;
};