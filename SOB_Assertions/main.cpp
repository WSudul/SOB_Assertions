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

	return 0;
}