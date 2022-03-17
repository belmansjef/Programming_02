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

Health& Health::operator-=(int rhs)
{
	m_Value -= rhs;
	return *this;
}

Health operator+(int lhs, Health rhs)
{
	return Health(rhs += lhs);
}

Health operator+(Health lhs, int rhs)
{
	return Health(lhs += rhs);
}

Health operator-(int lhs, Health rhs)
{
	return Health(rhs -= lhs);
}

Health operator-(Health lhs, int rhs)
{
	return Health(lhs -= rhs);
}
