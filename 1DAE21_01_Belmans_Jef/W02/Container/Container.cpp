#include "Container.h"

Container::Container(int capacity)
	: m_Size { 0 }
	, m_Capacity { capacity }
	, m_pElement { new int }
{
	for (int i = 1; i < m_Capacity; i++)
	{
		*(&m_pElement + (i * 4)) = new int;
	}
}

Container::~Container()
{
}

int Container::Size() const
{
	return m_Size;
}

int Container::Capacity() const
{
	return m_Capacity;
}

int Container::Get(int index) const
{
	return int(&m_pElement + (index * 4));
}

void Container::Set(int index, int newValue)
{
}

void Container::PushBack(int element)
{
}

void Container::Reserve(int newCapacity)
{
}
