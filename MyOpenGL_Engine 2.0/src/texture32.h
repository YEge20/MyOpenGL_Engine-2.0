#pragma once
#include "stb_image/stb_image.h"
#include <string>
#include"GL/glew.h"

class texture32
{
public:
	//初始化纹理创建，x为是否启用纹理的线性过滤
	texture32(const bool x);
	~texture32();

	//导入纹理到程序对应的插槽(position_of_texture,只能取值0~31)
	void importTexture(const std::string& filepath, const int position_of_texture);
	//绑了多个纹理后要启用其中纹理就使用此程序，把程序对应的插槽(position_of_texture_use)导入到要渲染的opengl插槽(slot,只能取值0~31)
	void bind(unsigned int slot, const int position_of_texture_use);
	void unbind();

	inline int GetChannel() { return m_channel; }
private:
	unsigned int m_texture[32];
	unsigned char* m_data;
	bool m_Linear;
	int m_channel;
};