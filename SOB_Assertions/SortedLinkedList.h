#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>

template<typename T>
struct Node
{
	T value;
	Node *N, *P;
	Node(double y)
	{
		value = y;
		N = P = NULL;
	}
};


template<typename T>
class SortedLinkedList
{
public:
	SortedLinkedList();
	~SortedLinkedList();

	bool Add(T x);
	bool PopFront(T x);
	bool PopBack(T x);
	unsigned long Size() const;
	std::string ToString() const;
	std::string ReversedToString() const;
	void clear();

};


template<typename T>
SortedLinkedList<T>::SortedLinkedList()
{
}


template<typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
}

template<typename T>
bool SortedLinkedList<T>::Add(T x)
{
	return false;
}

template<typename T>
bool SortedLinkedList<T>::PopFront(T x)
{
	return false;
}

template<typename T>
bool SortedLinkedList<T>::PopBack(T x)
{
	return false;
}

template<typename T>
unsigned long SortedLinkedList<T>::Size() const
{
	return 0;
}

template<typename T>
std::string SortedLinkedList<T>::ToString() const
{
	return std::string();
}

template<typename T>
std::string SortedLinkedList<T>::ReversedToString() const
{
	return std::string();
}

template<typename T>
void SortedLinkedList<T>::clear()
{
}



#endif