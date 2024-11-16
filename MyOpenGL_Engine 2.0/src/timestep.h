#pragma once
//���ڼ���ÿ֮֡���ʱ��Ȼ������������˶��ٶ������ǵ�ʵ��ʱ����ƥ�䣬��ֹ��Ϊ֡����Ӱ�����ǳ�����������˶��ٶ�
//һ�����Render�ļ��������Ⱦ����ʹ�����ӣ�����1+=����2*timestep
//�ر�˵����timestep�ĵ�λ���룬milltimestep�ĵ�λ�Ǻ���
class timestep
{
public:
	timestep(float time)
		:m_timestep(time)
	{
	}
	float GetSecond() { return m_timestep; }
	float GetMillSecond() { return 1000.0f * m_timestep; }
private:
	float m_timestep = 0;
};
