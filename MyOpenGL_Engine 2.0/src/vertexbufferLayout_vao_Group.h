#pragma once
#include<gl/glew.h>
//�˳�����������16��vao��vbo��veo�����
class vertexbufferLayout_vao_Group
{
public:
	//��ʼ������
	vertexbufferLayout_vao_Group();
	~vertexbufferLayout_vao_Group();

	//�������ע��vao_groupֻ����0~15
	void importVertex(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber, const int vao_group);
	//�������ʹ�ö�Ӧ�Ķ��㣬ע��vao_groupֻ����0~15
	void bind(const int vao_group);
	void unbind();
	//�������������Ӧ�Ķ������ݸ�ʽ��ע��vao_groupֻ����0~15
	void AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride, const int vao_group);
	unsigned int VAOid(const int vao_group);
	
private:
	unsigned int m_vao[16], m_vbo[16], m_veo[16], m_offset;
};