#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <sstream>
#include <functional>
#include <cassert>
#include <iostream>

template<typename T>
struct Node
{
	T value;
	Node *next;
	Node *previous;
	Node(T value)
	{
		this->value = value;
		next = previous = nullptr;
	}
};


template<typename T>
class SortedLinkedList
{
public:
	SortedLinkedList(std::function<bool(const T&, const T&)> comparator =
		[](const T &val_1, const T &val_2) { return val_1 > val_2; });
	~SortedLinkedList();

	bool Add(const T x);
	bool PopFront(const T x);
	bool PopBack(const T x);
	unsigned long Size() const;
	bool isEmpty() const;

	std::string ToString() const;
	std::string ReversedToString() const;
	void Clear();


private:

	Node<T>* CreateNode(const T& x);

	std::function<bool(const T&, const T&)> comparator_;
	unsigned long size_;
	Node<T>* head_;
	Node<T>* tail_;
};

template <typename T>
SortedLinkedList<T>::SortedLinkedList(
    std::function<bool(const T &, const T &)> comparator):
	comparator_(comparator), 
	size_(0), 
	head_(nullptr), 
	tail_(nullptr) {}

template<typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	Clear();
	//assert(0 == Size());
}

template<typename T>
bool SortedLinkedList<T>::Add(T x)
{
	auto new_node = CreateNode(x);
	if (isEmpty())
	{
		assert(nullptr == head_ && nullptr == tail_);
		head_ = new_node;
		tail_ = head_;
	}
	else if (1 == Size()) {
		if (!comparator_(head_->value, new_node->value))
		{
			//new tail
			new_node->previous = tail_;
			tail_->next = new_node; 
			tail_ = new_node;
		}
		else
		{
			//new head
			new_node->next = head_;
			head_-> previous = new_node;
			head_ = new_node;
		}

	}
	else
	{
		//#TODO refractor this to remove aboute else if
		//at least 2 nodes are present
		if (comparator_( head_->value, new_node->value))
		{
			//check if predicate is true for head - new head
			new_node->next = head_;
			head_->previous = new_node;
			head_ = new_node;
		}
		else if (!comparator_(tail_->value, new_node->value))
		{
			//check if predicate is false for tail - new tail
			new_node->previous = tail_;
			tail_->next = new_node;
			tail_ = new_node;
		}
		else {
			auto current_node = head_;
			while (current_node->next){
				
				bool comparator_current = comparator_(current_node->value, new_node->value);
				bool comparator_next = comparator_(current_node->next->value, new_node->value);

				if (!comparator_current && comparator_next)
					break;

				current_node = current_node->next;
			}

			auto next_node = current_node->next;
			auto previous_node = current_node->previous;
			new_node->previous = current_node;
			new_node->next = next_node;
			current_node->next = new_node;
			next_node->previous = new_node;			


		}





	}
	++size_;
	return true;
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
	assert(size_ >= 0);
	return size_;
}

template<typename T>
bool SortedLinkedList<T>::isEmpty() const
{
	return (0==Size());
}

template<typename T>
std::string SortedLinkedList<T>::ToString() const
{
	if (isEmpty())
		return std::string();

	std::stringstream stringstream;
	auto current_node = head_;

	do {
		stringstream << " " << current_node->value;
		current_node = current_node->next;
	} while (nullptr!=current_node);

	return stringstream.str();
}

template<typename T>
std::string SortedLinkedList<T>::ReversedToString() const
{
	if (isEmpty())
		return std::string();

	std::stringstream stringstream;
	auto current_node = tail_;

	do {
		stringstream << ' ';
		stringstream << current_node->value;
		current_node = current_node->previous;
	} while (nullptr != current_node);

	return stringstream.str();
}

template<typename T>
void SortedLinkedList<T>::Clear()
{

	//assert(0 == Size());
}

template<typename T>
inline Node<T>* SortedLinkedList<T>::CreateNode(const T & x)
{
	Node<T>* node = new Node<T>(x);
	return node;
}



#endif