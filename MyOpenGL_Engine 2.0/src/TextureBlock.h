#pragma once
#include "stb_image/stb_image.h"
#include<iostream>
#include <string>
#include"GL/glew.h"
#include<vector>
//注意：该API与texture32API有冲突，如果先调用了texture32的bind功能，则该API的bind功能失效
class TextureBlock
{
public:
	TextureBlock(std::vector<std::string> face,bool RGBAmode, bool LINEARmode);
	~TextureBlock();

	void bind();
	void unbind();

private:
	unsigned int m_texture;
};