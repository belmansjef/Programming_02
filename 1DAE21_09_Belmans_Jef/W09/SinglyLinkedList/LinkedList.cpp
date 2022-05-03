#include "LinkedList.h"

Node::Node(int value, Node *pNext)
	:value{ value }
	, pNext{ pNext }
{
}

LinkedList::LinkedList()
	: m_pFirstNode { nullptr }
	, m_Size { 0 }
{
}

LinkedList::~LinkedList()
{
	while (m_pFirstNode != nullptr)
	{
		Node* nextNode = m_pFirstNode->pNext;
		delete m_pFirstNode;
		m_pFirstNode = nullptr;
		m_pFirstNode = nextNode;
	}
}

// Wrap the value in a new Node object and add it as first Node of the list
void LinkedList::PushFront( int  value )
{
	Node* node{ new Node(value, m_pFirstNode) };
	m_pFirstNode = node;
	m_Size++;
}

// Remove and delete first Node
void LinkedList::PopFront( )
{
	if (m_pFirstNode == nullptr) return;

	Node* newFirstNode{ m_pFirstNode->pNext };
	delete m_pFirstNode;
	m_pFirstNode = newFirstNode;
	m_Size--;
}

// Remove all Nodes having this value
void LinkedList::Remove( int value )
{
	Node* temp = m_pFirstNode;
	Node* prev = nullptr;

	while (temp != nullptr)
	{
		if (temp != nullptr && prev == nullptr && temp->value == value)
		{
			m_pFirstNode = temp->pNext;
			delete temp;
			temp = m_pFirstNode;
			m_Size--;
		}
		else
		{
			if (temp->value == value)
			{
				prev->pNext = temp->pNext;
				delete temp;
				temp = prev->pNext;
				m_Size--;
			}
			else
			{
				prev = temp;
				temp = temp->pNext;
			}
		}
	}
}

// Wrap the value in a new Node object and insert it after the specified Node 
void LinkedList::InsertAfter( Node* pBefore, int value )
{
	Node* node{ new Node(value, pBefore->pNext) };
	pBefore->pNext = node;
	m_Size++;
}

// Return pointer to first Node
Node* LinkedList::Begin( ) const
{
	return m_pFirstNode;
}

// Return number of Node objects in the list
size_t LinkedList::Size( ) const
{
	return m_Size;
}

// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<( std::ostream& out, const LinkedList& list )
{
	Node* currNode{ list.Begin() };

	while (currNode != nullptr)
	{
		out << currNode->value << " ";
		currNode = currNode->pNext;
	}
	out << std::endl;
	return out;
}
