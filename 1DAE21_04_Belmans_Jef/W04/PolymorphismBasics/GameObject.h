#pragma once
#include <iostream>

class GameObject
{
public:
	enum class ObjectType 
	{
		enemy,
		pickup,
		weapon
	};

	ObjectType m_ObjectType;
	GameObject(int id, ObjectType type);
	virtual ~GameObject( );
	
	virtual std::string ToString() const = 0;
protected:
	int m_Id;

private: 
};
