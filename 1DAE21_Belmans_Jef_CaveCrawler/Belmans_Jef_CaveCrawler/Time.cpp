#include "Time.h"
#include "pch.h"

Time* Time::GetInstance()
{
	static Time* t = new Time();
	return t;
}

Time::Time()
	: m_TimeScale{ 1.0f }
	, m_DeltaTime { 0.0f }
	, m_Time { 0.0f }
{

}
