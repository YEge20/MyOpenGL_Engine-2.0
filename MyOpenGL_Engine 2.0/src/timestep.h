#pragma once
//用于计算每帧之间的时间差，然后修正物体的运动速度与我们的实际时间相匹配，防止因为帧数而影响我们场景中物体的运动速度
//一般情况Render文件里面的渲染程序使用例子：参数1+=参数2*timestep
//特别说明：timestep的单位是秒，milltimestep的单位是毫秒
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
