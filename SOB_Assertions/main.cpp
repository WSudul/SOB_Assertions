/* SOB - lab 1*/


#include <iostream>
#include <memory>

#include "FileWrapper.h"
#include "SortedLinkedList.h"


int main(int argc, char** argv) {

	std::unique_ptr<IFileWrapper> file_wrapper = std::make_unique<FileWrapper>();
	std::unique_ptr<SortedLinkedList<double>> linked_list_double = std::make_unique<SortedLinkedList<double>>();
	std::unique_ptr<SortedLinkedList<int>> linked_list_int = std::make_unique<SortedLinkedList<int>>();

	std::cout << "Hello" << std::endl;

	assert(linked_list_int->Add(1));
	assert(linked_list_int->Add(2));
	assert(linked_list_int->Add(5));
	assert(linked_list_int->Add(3));
	assert(linked_list_int->Add(4));
	assert(5 == linked_list_int->Size());
	std::cout << linked_list_int->ToString() << std::endl;
	std::cout << linked_list_int->ReversedToString() << std::endl;

    std::cout << file_wrapper->Open("numbers.txt", std::ios::in);
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	file_wrapper->Close();
	return 0;
}