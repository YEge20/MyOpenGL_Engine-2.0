#include "DrawBlock.h"

DrawBlock::DrawBlock(float X, float Y, float Z)
	:m_sizeX(abs(X)/2),m_sizeY(abs(Y)/2),m_sizeZ(abs(Z)/2),m_slot_use(0),m_slot_checker{false}
{
#define face 32  //数据的数组的大小
#define layoutelement 6 //布局数组的大小
#define indexsize 3 //数据格式的数组大小

	float faceUP[face] = {
		//vertex:                   //uv:                //normalize:
		 m_sizeX, m_sizeY, m_sizeZ,    1.0f,0.0f,         0.0f,1.0f,0.0f,//0
		-m_sizeX, m_sizeY, m_sizeZ,    0.0f,0.0f,         0.0f,1.0f,0.0f,//1
		 m_sizeX, m_sizeY,-m_sizeZ,    1.0f,1.0f,         0.0f,1.0f,0.0f,//2
		-m_sizeX, m_sizeY,-m_sizeZ,    0.0f,1.0f,         0.0f,1.0f,0.0f,//3
	};
	float faceDOWN[face] = {
		//vertex:                   //uv:                //normalize:
		 m_sizeX,-m_sizeY, m_sizeZ,    1.0f,0.0f,        0.0f,-1.0f,0.0f,//0
		-m_sizeX,-m_sizeY, m_sizeZ,    0.0f,0.0f,        0.0f,-1.0f,0.0f,//1
		 m_sizeX,-m_sizeY,-m_sizeZ,    1.0f,1.0f,        0.0f,-1.0f,0.0f,//2
		-m_sizeX,-m_sizeY,-m_sizeZ,    0.0f,1.0f,        0.0f,-1.0f,0.0f //3
	};
	float faceLEFT[face] = {
		//vertex:                   //uv:                //normalize:
		-m_sizeX, m_sizeY, m_sizeZ,    1.0f,1.0f,        -1.0f,0.0f,0.0f,//0
		-m_sizeX,-m_sizeY, m_sizeZ,    1.0f,0.0f,        -1.0f,0.0f,0.0f,//1
		-m_sizeX, m_sizeY,-m_sizeZ,    0.0f,1.0f,        -1.0f,0.0f,0.0f,//2
		-m_sizeX,-m_sizeY,-m_sizeZ,    0.0f,0.0f,        -1.0f,0.0f,0.0f //3
	};
	float faceRIGHT[face] = {
		//vertex:                   //uv:                //normalize:
		 m_sizeX, m_sizeY, m_sizeZ,    1.0f,1.0f,         1.0f,0.0f,0.0f,//0
		 m_sizeX,-m_sizeY, m_sizeZ,    1.0f,0.0f,         1.0f,0.0f,0.0f,//1
		 m_sizeX, m_sizeY,-m_sizeZ,    0.0f,1.0f,         1.0f,0.0f,0.0f,//2
		 m_sizeX,-m_sizeY,-m_sizeZ,    0.0f,0.0f,         1.0f,0.0f,0.0f //3
	};
	float faceFRONT[face] = {
		//vertex:                   //uv:                //normalize:
		 m_sizeX, m_sizeY, m_sizeZ,    1.0f,1.0f,         0.0f,0.0f,1.0f,//0
		-m_sizeX, m_sizeY, m_sizeZ,    0.0f,1.0f,         0.0f,0.0f,1.0f,//1
		 m_sizeX,-m_sizeY, m_sizeZ,    1.0f,0.0f,         0.0f,0.0f,1.0f,//2
		-m_sizeX,-m_sizeY, m_sizeZ,    0.0f,0.0f,         0.0f,0.0f,1.0f //3
	};
	float faceBACK[face] = {
		//vertex:                   //uv:                //normalize:
		 m_sizeX, m_sizeY,-m_sizeZ,    1.0f,1.0f,         0.0f,0.0f,-1.0f,//0
		-m_sizeX, m_sizeY,-m_sizeZ,    0.0f,1.0f,         0.0f,0.0f,-1.0f,//1
		 m_sizeX,-m_sizeY,-m_sizeZ,    1.0f,0.0f,         0.0f,0.0f,-1.0f,//2
		-m_sizeX,-m_sizeY,-m_sizeZ,    0.0f,0.0f,         0.0f,0.0f,-1.0f //3
	};
	unsigned int layout[layoutelement] =
	{
		0,1,2,
		1,2,3
	};
	int index[indexsize] =
	{
		3,2,3
	};
	int stride = 0;
	for (int i = 0; i < indexsize; i++)
		stride += index[i];

	m_vao.reset(new vertexbufferLayout_vao_Group());
	m_vao->importVertex(faceUP, layout, face, layoutelement, 0);
	m_vao->AttribPointer(indexsize, index, stride, 0);
	m_vao->importVertex(faceDOWN, layout, face, layoutelement, 1);
	m_vao->AttribPointer(indexsize, index, stride, 1);
	m_vao->importVertex(faceLEFT, layout, face, layoutelement, 2);
	m_vao->AttribPointer(indexsize, index, stride, 2);
	m_vao->importVertex(faceRIGHT, layout, face, layoutelement, 3);
	m_vao->AttribPointer(indexsize, index, stride, 3);
	m_vao->importVertex(faceFRONT, layout, face, layoutelement, 4);
	m_vao->AttribPointer(indexsize, index, stride, 4);
	m_vao->importVertex(faceBACK, layout, face, layoutelement, 5);
	m_vao->AttribPointer(indexsize, index, stride, 5);
}

void DrawBlock::ImportTexture(const std::vector<std::string> texture6, bool linear, SlotControlerID slot_controler)
{
	switch (slot_controler)
	{
	case SlotID_1:
		for (int i = 0; i < 6; i++)
			m_texture_controler[i].reset(new texture(texture6[i].c_str(), linear));
		if (m_slot_checker[0] == false)
		{
			m_slot_use++;
			m_slot_checker[0] = true;
		}
		break;
	case SlotID_2:
		for (int i = 0; i < 6; i++)
			m_texture_controler2[i].reset(new texture(texture6[i].c_str(), linear));
		if (m_slot_checker[1] == false)
		{
			m_slot_use++;
			m_slot_checker[1] = true;
		}
		break;
	case SlotID_3:
		for (int i = 0; i < 6; i++)
			m_texture_controler3[i].reset(new texture(texture6[i].c_str(), linear));
		if (m_slot_checker[2] == false)
		{
			m_slot_use++;
			m_slot_checker[2] = true;
		}
		break;
	}
}

void DrawBlock::DrawCallTexture(unsigned int GLTexture_slot, unsigned int GLTexture_slot2, unsigned int GLTexture_slot3)
{
	//绘画顺序：上->下->左->右->前->后
	switch (m_slot_use)
	{
	case 1:
		for (int i = 0; i < 6; i++)
		{
			m_vao->bind(i);
			m_texture_controler[i]->bind(GLTexture_slot);
			glDrawElements(GL_TRIANGLES, layoutelement, GL_UNSIGNED_INT, nullptr);
		}
		break;
	case 2:
		for (int i = 0; i < 6; i++)
		{
			m_vao->bind(i);
			m_texture_controler[i]->bind(GLTexture_slot);
			m_texture_controler2[i]->bind(GLTexture_slot2);
			glDrawElements(GL_TRIANGLES, layoutelement, GL_UNSIGNED_INT, nullptr);
		}
		break;
	case 3:
		for (int i = 0; i < 6; i++)
		{
			m_vao->bind(i);
			m_texture_controler[i]->bind(GLTexture_slot);
			m_texture_controler2[i]->bind(GLTexture_slot2);
			m_texture_controler3[i]->bind(GLTexture_slot3);
			glDrawElements(GL_TRIANGLES, layoutelement, GL_UNSIGNED_INT, nullptr);
		}
		break;
	}
}

void DrawBlock::DrawCall()
{	
	//绘画顺序：上->下->左->右->前->后
	for (int i = 0; i < 6; i++)
	{
		m_vao->bind(i);
		glDrawElements(GL_TRIANGLES, layoutelement, GL_UNSIGNED_INT, nullptr);
	}
}
