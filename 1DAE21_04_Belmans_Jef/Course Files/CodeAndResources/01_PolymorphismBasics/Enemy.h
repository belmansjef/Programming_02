#pragma once
#include "GameObject.h"
#include <string>


class Enemy : public GameObject
{
public:
	Enemy( );
	~Enemy( );

	std::string ToString( ) const;

private:
	static int m_InstanceCounter;
};


 
