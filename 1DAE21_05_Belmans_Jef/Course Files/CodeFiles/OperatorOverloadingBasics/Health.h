#pragma once

class Health final
{
public:
	Health( int value); 
	int GetValue( ) const;

private:
	int m_Value;
};
