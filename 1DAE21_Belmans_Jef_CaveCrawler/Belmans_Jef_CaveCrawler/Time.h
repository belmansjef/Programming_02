#pragma once
class Time
{
public:
	static float time;
	static float deltaTime;

	static void SetTimeScale(float scale);
	static float GetTimeScale();

private:
	static float m_TimeScale;
};

