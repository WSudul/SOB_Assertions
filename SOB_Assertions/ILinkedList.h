#ifndef I_LINKED_LIST_H
#define I_LINKED_LIST_H

#include <string>




template<typename T>
class ILinkedList {
public:
	virtual ~ILinkedList() {};

	virtual bool Add(T x)=0;
	virtual bool PopFront(T x)=0;
	virtual bool PopBack(T x) = 0;
	virtual unsigned long Size() const = 0;
	virtual std::string ToString() const =0;
	virtual std::string ReversedToString() const =0;
	virtual void clear()=0;


};


#endif // !I_LINKED_LIST_H
