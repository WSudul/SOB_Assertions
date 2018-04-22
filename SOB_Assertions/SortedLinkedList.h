#ifndef LINKED_LIST_H
#define LINKED_LIST_H


//#define NDEBUG
#include <cassert>
#include <string>
#include <sstream>
#include <functional>
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
	bool PopFront();
	bool PopBack();
	unsigned long Size() const;
	bool isEmpty() const;

	std::string ToString() const;
	std::string ReversedToString() const;
	void Clear();


private:

	Node<T>* CreateNode(const T& x);

	std::function<bool(const T&, const T&)> comparator_;
	long long size_;
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
	assert(0 == Size());
}

template<typename T>
bool SortedLinkedList<T>::Add(T x)
{
	auto new_node = CreateNode(x);
	assert(new_node != nullptr);
	if (!new_node)
		return false;

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
				bool comparator_next = comparator_(current_node->next->value, new_node->value);
				if (comparator_next)
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
bool SortedLinkedList<T>::PopFront()
{
	if (isEmpty()) {
		return false;
	}
	else if (head_ == tail_) {
		delete head_;
		head_ = nullptr;
		tail_ = nullptr;
		--size_;
		return true;
	}
	else {
		auto temp = head_;
		auto next = head_->next;
		next->previous = nullptr;
		head_ = next;
		delete temp;
		temp = nullptr;
		--size_;
		return true;
	}
}

template<typename T>
bool SortedLinkedList<T>::PopBack()
{
	if (isEmpty()) {
		return false;
	}
	
	else if (head_ == tail_) {
		delete tail_;
		tail_ = nullptr;
		head_ = nullptr;
		--size_;
		return true;
	}
	else {
		auto temp = tail_;
		auto prev = tail_->previous;
		prev->next = nullptr;
		tail_ = prev;
		delete temp;
		temp = nullptr;
		--size_;
		return true;
	}

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
	assert(size_ >= 0);
	return (0==Size());
}

template<typename T>
std::string SortedLinkedList<T>::ToString() const
{
	if (isEmpty())
		return std::string();

	assert(head_);
	assert(tail_);
	std::stringstream stringstream;
	stringstream << "head_: " << head_->value <<"\t";
	stringstream << "tail_: " << tail_->value << "\t";
	stringstream << "[";

	auto current_node = head_;
	do {
		stringstream << " " << current_node->value;
		current_node = current_node->next;
		
	} while (nullptr!=current_node);
	stringstream << "]";

	return stringstream.str();
}

template<typename T>
std::string SortedLinkedList<T>::ReversedToString() const
{
	if (isEmpty())
		return std::string();

	assert(head_);
	assert(tail_);
	std::stringstream stringstream;
	stringstream << "head_: " << head_->value << "\t";
	stringstream << "tail_: " << tail_->value << "\t";
	stringstream << "[";

	auto current_node = tail_;
	do {
		stringstream << ' ';
		stringstream << current_node->value;
		current_node = current_node->previous;
	} while (nullptr != current_node);
	stringstream << "]";

	return stringstream.str();
}

template<typename T>
void SortedLinkedList<T>::Clear()
{
	while (!isEmpty()) {
		PopBack();

	}
	assert(0 == Size());
}

template<typename T>
inline Node<T>* SortedLinkedList<T>::CreateNode(const T & x)
{
	try {
		Node<T>* node = new Node<T>(x);
		return node;
	}
	catch (std::bad_alloc& exception) {
		std::cout << "exception caught: " << exception.what() << std::endl;
		return nullptr;
	}

	
}



#endif