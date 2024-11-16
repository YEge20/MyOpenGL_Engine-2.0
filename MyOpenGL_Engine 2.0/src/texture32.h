#pragma once
#include "stb_image/stb_image.h"
#include <string>
#include"GL/glew.h"

class texture32
{
public:
	//��ʼ����������xΪ�Ƿ�������������Թ���
	texture32(const bool x);
	~texture32();

	//�������������Ӧ�Ĳ��(position_of_texture,ֻ��ȡֵ0~31)
	void importTexture(const std::string& filepath, const int position_of_texture);
	//���˶�������Ҫ�������������ʹ�ô˳��򣬰ѳ����Ӧ�Ĳ��(position_of_texture_use)���뵽Ҫ��Ⱦ��opengl���(slot,ֻ��ȡֵ0~31)
	void bind(unsigned int slot, const int position_of_texture_use);
	void unbind();

	inline int GetChannel() { return m_channel; }
private:
	unsigned int m_texture[32];
	unsigned char* m_data;
	bool m_Linear;
	int m_channel;
};