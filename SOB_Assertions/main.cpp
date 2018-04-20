/* SOB - lab 1*/


#include <iostream>
#include <memory>

#include "FileWrapper.h"
#include "SortedLinkedList.h"

enum  TypeOption  {
	INT = 1,
	DOUBLE=2,
	UNKNOWN=99
};
#include <type_traits> //for std::underlying_type

typedef std::underlying_type<TypeOption>::type utype;
namespace option{
	constexpr auto arg_start = '-';
	constexpr auto file = 'f';
	constexpr auto type = 't';
	constexpr auto range = 'r';

	constexpr auto int_type = "int";
	constexpr auto double_type = "double";
}


template<typename T>
void TestLinkedList(std::unique_ptr<SortedLinkedList<T>>& list);

template <typename typeOUT, typename typeSIZE1, typename typeSIZE2>
typeOUT **ftab(typeSIZE1 w, typeSIZE2 k, typeOUT **t);
/*
TEST DATA!
char data_test_array[8][32]{
{"skip.exe"},
{ "-t" },{ "int" },
{ "-f" },{ "test.txt" },
{ "-r" },{ "-5\0" },{ "100\0" }

example of arguments via console:
-f tes.txt -r 10 300 -t int
*/

int main(int argc, char** argv) {

	std::unique_ptr<IFileWrapper> file_wrapper = std::make_unique<FileWrapper>();
	std::unique_ptr<SortedLinkedList<double>> linked_list_double = std::make_unique<SortedLinkedList<double>>();
	std::unique_ptr<SortedLinkedList<int>> linked_list_int = std::make_unique<SortedLinkedList<int>>();
	std::unique_ptr<SortedLinkedList<int>> linked_list_int_customer_comparator = std::make_unique<SortedLinkedList<int>>([](const int& v1, const int&v2) {return v1 < v2; });
	std::cout << "Hello" << std::endl;
	TestLinkedList(linked_list_double);
	TestLinkedList(linked_list_int);
	TestLinkedList(linked_list_int_customer_comparator);
	
	assert(argc > 2);
	std::string file_path;
	TypeOption type_option= TypeOption::UNKNOWN;
	std::string min;
	std::string max;

	for (int i = 1; i < argc; ++i) {
		auto argument=std::string(argv[i]);
		assert(!argument.empty());
		if (argument.at(0) == option::arg_start) {
			if (argument.at(1) == option::file) {
				assert(i + 1 < argc);
				file_path = argv[i+ 1];
				++i;

			}
			else if (argument.at(1) == option::type) {

				assert(i + 1 < argc);
				std::string type = argv[i + 1];
				if (type == option::int_type)
					type_option = TypeOption::INT;
				else if (type == option::double_type)
					type_option = TypeOption::DOUBLE;
				
				assert(TypeOption::UNKNOWN != type_option);

				++i;
			}
			else if (argument.at(1) == option::range) {
				assert(i + 2 < argc);
				min = argv[i + 1];
				max = argv[i + 2];

				i += 2;
				assert(!min.empty());
				assert(!max.empty());
			}
			else 
			{
				std::cout << "Unknown argument: " << argv[i] << std::endl;
				return -1;
			}
		}


	}


	assert(!file_path.empty());
	assert(!min.empty());
	assert(!max.empty());
	assert(TypeOption::UNKNOWN != type_option);
	std::cout << file_path << "\t" << type_option << "\t" << min << "\n" << std::stoi(max) << std::endl;


    std::cout << file_wrapper->Open("numbers.txt", std::ios::in);
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	std::cout << file_wrapper->ReadWord() << std::endl;
	file_wrapper->Close();
	return 0;
}


template<typename T>
void TestLinkedList(std::unique_ptr<SortedLinkedList<T>>& list) {

	assert(list->Add(1));
	assert(list->Add(2));
	assert(list->Add(5));
	assert(list->Add(3));
	assert(list->Add(4));
	assert(5 == list->Size());
	std::cout << list->ToString() << std::endl;
	std::cout << list->ReversedToString() << std::endl;

}