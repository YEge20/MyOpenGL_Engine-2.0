#pragma once
#include<gl/glew.h>
//此程序允许塞进16个vao和vbo和veo组管理
class vertexbufferLayout_vao_Group
{
public:
	//初始化程序
	vertexbufferLayout_vao_Group();
	~vertexbufferLayout_vao_Group();

	//导入程序，注意vao_group只能填0~15
	void importVertex(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber, const int vao_group);
	//导入完后使用对应的顶点，注意vao_group只能填0~15
	void bind(const int vao_group);
	void unbind();
	//导入完后设置相应的顶点数据格式，注意vao_group只能填0~15
	void AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride, const int vao_group);
	unsigned int VAOid(const int vao_group);
	
private:
	unsigned int m_vao[16], m_vbo[16], m_veo[16], m_offset;
};