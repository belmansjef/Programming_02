#pragma once

class GameObject
{
public:
	GameObject(int id );
	~GameObject( );
	// Implicitly defined copy/move constructors and operator= are ok

protected:
	int m_Id;

private: 
};



