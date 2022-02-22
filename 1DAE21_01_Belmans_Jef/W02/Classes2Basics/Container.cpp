#include "Container.h"

Container::Container(int capacity)
	: m_Size{ 0 }
{
	Reserve(capacity);
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
	return m_pElement[index];
}

void Container::Set(int index, int newValue)
{
	m_pElement[index] = newValue;
}

void Container::PushBack(int element)
{
	++m_Size;

	if (m_Size > m_Capacity)
	{
		Reserve((m_Size * 2) + 1);
	}

	m_pElement[m_Size - 1] = element;

}

void Container::Reserve(int newCapacity)
{
	int* newContainer = new int[newCapacity];

	if (m_pElement)
	{
		int currentSize{ m_Size };
		if (m_Capacity < currentSize)
		{
			currentSize = m_Capacity;
		}

		for (int i = 0; i < currentSize; i++)
		{
			newContainer[i] = m_pElement[i];
		}

		delete[] m_pElement;
		m_pElement = nullptr;
	}

	m_pElement = newContainer;
	m_Capacity = newCapacity;
}
