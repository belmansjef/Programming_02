#include "pch.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject(int id, ObjectType type)
	:m_Id{ id }
	, m_ObjectType { type }
{
	std::cout << ">GameObject constructor<\n";
}

GameObject::~GameObject( )
{
	std::cout << ">GameObject destructor<\n";
}

