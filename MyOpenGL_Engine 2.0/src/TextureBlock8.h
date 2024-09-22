#pragma once
#include "stb_image/stb_image.h"
#include<iostream>
#include <string>
#include"GL/glew.h"
#include<vector>
//ע�⣺��API��texture32API�г�ͻ������ȵ�����texture32��bind���ܣ����API��bind����ʧЧ
class TextureBlock8
{
public:
	TextureBlock8(bool RGBAmode, bool LINEARmode);//��һ������Ϊ�Ƿ�ʹ��RGBA�洢(Ĭ��ΪRGB),�ڶ�������Ϊ�Ƿ�ʹ��LINEAR����(Ĭ��ΪNEAREST)
	~TextureBlock8();

	void importtexture(std::vector<std::string> face, int slot);
	void bind(int slot);
	void unbind();

private:
	unsigned int m_texture[8];
	unsigned char* m_data;
	bool m_RGB, m_LINEAR;
};