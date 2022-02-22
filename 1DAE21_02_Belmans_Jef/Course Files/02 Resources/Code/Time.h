#pragma once

class Time
{
public:
	Time( int seconds );
	Time( int seconds, int minutes );
	Time( int seconds, int minutes, int hours );

	void Print( );
	int GetSeconds( );
	int GetMinutes( );
	int GetHours( );

	void AddSeconds( int seconds );
	void AddMinutes( int minutes );
	void AddHours( int hours );

private:
	int m_Seconds{};
};