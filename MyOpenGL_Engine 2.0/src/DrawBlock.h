#pragma once
#include<memory>
#include<vector>
#include<string>
#include"vertexbufferLayout_vao_Group.h"
#include"texture.h"
enum SlotControlerID
{
	SlotID_1 = 1, SlotID_2, SlotID_3
};

class DrawBlock
{
public:
	//初始化程序，告诉程序该方块的长宽高（分别为XYZ）
	DrawBlock(float X, float Y, float Z);
	//导入各个面的材质，最多只能导入三组材质！
	//注意：如果只使用一组材质，则SlotControlerID填SlotID_1，例子：ImportTexture(face,false,SlotID_1)；
	//如果使用两组则分别使用SlotID_1与SlotID_2,例子：ImportTexture(face1,false,SlotID_1)；ImportTexture(face2,false,SlotID_2)；
	//以此类推三组的使用
	void ImportTexture(const std::vector<std::string> texture6, bool linear, SlotControlerID slot_controler);
	//材质绘画调用命令，参数说明：GLTexture_slot,GLTexture_slot2,GLTexture_slot3分别是三个插槽将要使用的GL_TEXTURE插槽，
	//注意：不要忘记在你的着色器里声明对应的sampler2D的变量的整数值，这个值对应你的GL_TEXTURE插槽值
	void DrawCallTexture(unsigned int GLTexture_slot, unsigned int GLTexture_slot2, unsigned int GLTexture_slot3);
	void DrawCall();
	inline int slotuse() { return m_slot_use; }//调试用而已,查看材质插槽已使用的数量
	inline bool SetSlot_checker(int slot, bool y) { m_slot_checker[slot] = y; }//调试用而已,slot只能为0~2，y为设置它当前的bool值
private:
	float m_sizeX,m_sizeY,m_sizeZ;
	int m_slot_use;
	bool m_slot_checker[3];
	std::vector<std::string> m_texture;
	std::shared_ptr<texture> m_texture_controler[6];
	std::shared_ptr<texture> m_texture_controler2[6];
	std::shared_ptr<texture> m_texture_controler3[6];
	std::shared_ptr<vertexbufferLayout_vao_Group> m_vao;
};

