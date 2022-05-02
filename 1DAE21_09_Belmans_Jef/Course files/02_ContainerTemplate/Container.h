#pragma once
#include <initializer_list>

class Container
{
public:
	explicit Container( int capacity = 10); 
	Container(const std::initializer_list<int>& list);
	Container( const Container& other );
	Container& operator=( const Container& other );
	Container( Container&& other )noexcept;           
	Container& operator=( Container&& other )noexcept;
	~Container( );

	int Size( ) const;
	int Capacity( ) const;
	int Get( int index ) const;
	void Set( int index, int value );
	void PushBack( int element );
	int& operator[]( int index ); 
	const int& operator[]( int index ) const;

private:
	int m_Size;
	int m_Capacity;
	int *m_pElements;

	void Reserve( int newCapacity );
};
