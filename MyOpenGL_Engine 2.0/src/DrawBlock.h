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
	DrawBlock(float X, float Y, float Z);
	void ImportTexture(const std::vector<std::string> texture6, bool linear, SlotControlerID slot_controler);
	void DrawCallTexture(unsigned int GLTexture_slot, unsigned int GLTexture_slot2, unsigned int GLTexture_slot3);
	void DrawCall();
	inline int slotuse() { return m_slot_use; }//调试用而已
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

