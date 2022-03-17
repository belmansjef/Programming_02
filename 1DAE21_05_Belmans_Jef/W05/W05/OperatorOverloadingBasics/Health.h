#pragma once
class Health final
{
public:
	Health( int value); 
	int GetValue( ) const;
	Health& operator+=(int rhs);
	Health& operator-=(int rhs);

private:
	int m_Value;
};

Health operator+(int lhs, Health rhs);
Health operator+(Health lhs, int rhs);

Health operator-(int lhs, Health rhs);
Health operator-(Health lhs, int rhs);

