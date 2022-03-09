#pragma once
#include "GameObject.h"
#include <string>


class PickUp : public GameObject
{
public:
	PickUp( );
	~PickUp( );

	virtual std::string ToString( ) const override;

private:
	static int m_InstanceCounter;
};
