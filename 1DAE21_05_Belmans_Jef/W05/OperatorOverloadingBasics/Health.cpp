#include "pch.h"
#include "Health.h"

Health::Health( int value) 
	: m_Value{value}
{
}
int Health::GetValue( ) const
{
	return m_Value;
}

Health& Health::operator+=(int rhs)
{
	m_Value += rhs;
	return	*this;
}

Health& Health::operator+=(const Health& rhs)
{
	m_Value += rhs.GetValue();
	return *this;
}

Health& Health::operator-=(int rhs)
{
	m_Value -= rhs;
	return *this;
}

Health& Health::operator-=(const Health& rhs)
{
	m_Value -= rhs.GetValue();
	return *this;
}

int operator+(Health& lhs, const int& rhs)
{
	return lhs.GetValue() + rhs;
}

int operator+(int& lhs, const Health& rhs)
{
	return lhs + rhs.GetValue();
}

int operator-(Health& lhs, const int& rhs)
{
	return lhs.GetValue() - rhs;
}

int operator-(int& lhs, const Health& rhs)
{
	return lhs - rhs.GetValue();
}