#include "Time.h"

float Time::time{ 0.0f };
float Time::deltaTime{ 0.0f };
float Time::m_TimeScale{ 1.0f };

void Time::SetTimeScale(float scale)
{
	m_TimeScale = scale;
}

float Time::GetTimeScale()
{
	return m_TimeScale;
}
