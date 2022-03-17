#pragma once
class Health final
{
public:
	Health( int value); 
	int GetValue( ) const;
	Health& operator+=(int rhs);
	Health& operator+=(const Health& rhs);
	Health& operator-=(int rhs);
	Health& operator-=(const Health& rhs);

private:
	int m_Value;
};

int operator+(int& lhs, const Health& rhs);
int operator+(Health& lhs, const int& rhs);

int operator-(int& lhs, const Health& rhs);
int operator-(Health& lhs, const int& rhs);