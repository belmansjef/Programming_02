#pragma once
class Time
{
public:
	static Time* GetInstance();
	float m_Time;
	float m_DeltaTime;
	float m_TimeScale;

private:
	Time();
};

