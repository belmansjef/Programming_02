#include "pch.h"
#include "Container.h"
#include <cassert>

Container::Container( int capacity ) 
	: m_Size{ 0 }
	, m_Capacity{ capacity }
	, m_pElement{ new int[capacity] }
{
}

Container::Container(const Container& other)
	: m_Size { other.m_Size }
	, m_Capacity { other.m_Capacity }
	, m_pElement { new int[other.m_Capacity] }
{
	for (size_t i = 0; i < m_Size; i++)
	{
		m_pElement[i] = other.m_pElement[i];
	}
}

Container::Container(Container&& other) noexcept
	: m_Size { other.m_Size }
	, m_Capacity { other.m_Capacity }
	, m_pElement { other.m_pElement }
{
	other.m_pElement = nullptr;
	other.m_Size = 0;
	other.m_Capacity = 0;
}

Container& Container::operator=(Container&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_pElement;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		m_pElement = other.m_pElement;
		other.m_pElement = nullptr;
		other.m_Size = 0;
		other.m_Capacity = 0;
	}

	return *this;
}

Container::~Container( ) 
{ 
	delete[] m_pElement; 
}

int Container::Size( ) const
{ 
	return m_Size; 
}

int Container::Capacity( ) const
{
	return m_Capacity;
}

int Container::Get( int index ) const
{
	assert( index >= 0 && index < m_Size );
	return m_pElement[index];
}

void Container::Set( int index, int value )
{
	assert( index >= 0 && index < m_Size );
	m_pElement[index] = value;
}

void Container::PushBack( int value )
{
	if ( !( m_Size < m_Capacity ) )
	{
		Reserve( m_Capacity * 2  + 1);
	}
	m_pElement[m_Size] = value;
	++m_Size;
}

//int Container::operator[](int index) const
int& Container::operator[](int index) 
{
	assert(index >= 0 && index < m_Size);
	return m_pElement[index];
}

int Container::operator[](int index) const
{
	assert(index >= 0 && index < m_Size);
	return m_pElement[index];
}

Container& Container::operator=(const Container& other)
{
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_pElement = new int[other.m_Capacity];

	for (size_t i = 0; i < m_Size; i++)
	{
		m_pElement[i] = other.m_pElement[i];
	}

	return *this;
}

void Container::Reserve( int newCapacity )
{
	if ( newCapacity <= m_Capacity )
	{
		return;
	}

	// Dynamically allocate memory
	int * pNew = new int[newCapacity] {};
	// Copy the elements into this new memory
	for ( int i{ 0 }; i < m_Size; ++i )
	{
		pNew[i] = m_pElement[i];
	}
	// Free the old memory
	delete[] m_pElement;

	// Adapt the data members to this new situation
	m_pElement = pNew;
	m_Capacity = newCapacity;
}



