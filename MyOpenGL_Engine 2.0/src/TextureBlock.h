#pragma once
#include "stb_image/stb_image.h"
#include<iostream>
#include <string>
#include"GL/glew.h"
#include<vector>
//ע�⣺��API��texture32API�г�ͻ������ȵ�����texture32��bind���ܣ����API��bind����ʧЧ
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