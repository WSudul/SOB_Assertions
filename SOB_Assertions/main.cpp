/* SOB - lab 1*/


#include <iostream>
#include <memory>
#include <vector>

#include "FileWrapper.h"
#include "SortedLinkedList.h"

enum  TypeOption  {
	INT = 1,
	DOUBLE=2,
	UNKNOWN=99
};

namespace option {
	constexpr auto arg_start = '-';
	constexpr auto file = 'f';
	constexpr auto type = 't';
	constexpr auto range = 'r';

	constexpr auto int_type = "int";
	constexpr auto double_type = "double";

	struct configuration {
		std::string file_path="data.txt";
		TypeOption type_option = TypeOption::UNKNOWN;
		std::string min="-100";
		std::string max="100";
	};
}


template<typename T>
void TestLinkedList(std::unique_ptr<SortedLinkedList<T>>& list);

option::configuration ParseArguments(int argc, char** argv);
/*

example of arguments via console:
-f test.txt -r 10 300 -t int
*/

int main(int argc, char** argv) {

	std::unique_ptr<IFileWrapper> file_wrapper = std::make_unique<FileWrapper>();
	std::unique_ptr<SortedLinkedList<double>> linked_list_double = std::make_unique<SortedLinkedList<double>>();
	std::unique_ptr<SortedLinkedList<int>> linked_list_int = std::make_unique<SortedLinkedList<int>>();
	std::unique_ptr<SortedLinkedList<int>> linked_list_int_customer_comparator = std::make_unique<SortedLinkedList<int>>([](const int& v1, const int&v2) {return v1 < v2; });
	std::cout << "Hello" << std::endl;


	option::configuration config;
	config = ParseArguments(argc, argv);
	/* test config*/
	config = { "data.txt",TypeOption::INT,"-100","100" };

	
	assert(!config.file_path.empty());
	assert(!config.min.empty());
	assert(!config.max.empty());
	assert((std::stod(config.max) - std::stod(config.min)) >= 0);
	assert(TypeOption::UNKNOWN != config.type_option);
	std::cout << config.file_path << "\t" << config.type_option << "\t" << config.min << "\t" << config.max << std::endl;

	std::vector<std::string> words;

	switch(config.type_option) {
	case TypeOption::INT: 
	{
		for (auto& word : words) {
			int value = std::stoi(word);
			linked_list_int->Add(value);
		}
		std::cout << linked_list_int->ToString();
		std::cout << linked_list_int->ReversedToString();


	}
	break;
	case TypeOption::DOUBLE:
	{
		for (auto& word : words) {
			double value = std::stod(word);
			linked_list_double->Add(value);
		}
		std::cout << linked_list_double->ToString();
		std::cout << linked_list_double->ReversedToString();

	}
	break;
	default:
		std::cout << "Unsupported option activated" << std::endl;
	}

	//cleanup for tests
	linked_list_int.reset(new SortedLinkedList<int>());
	linked_list_double.reset(new SortedLinkedList<double>());

	TestLinkedList(linked_list_double);
	TestLinkedList(linked_list_int);
	TestLinkedList(linked_list_int_customer_comparator);


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
	std::cout << "*-------------------*" << std::endl;
	std::cout << "*---Start of test---*" << std::endl;
	assert(list->isEmpty());
	assert(list->Add(1));
	assert(list->Add(2));
	assert(list->Add(5));
	assert(list->Add(3));
	assert(list->Add(4));
	assert(5 == list->Size());
	std::cout << list->ToString() << std::endl;
	std::cout << list->ReversedToString() << std::endl;
	
	std::cout << "-------------------"<<std::endl;
	assert(list->PopFront());
	assert(list->PopBack());
	assert(3 == list->Size());
	std::cout << list->ToString() << std::endl;
	std::cout << list->ReversedToString() << std::endl;


	std::cout << "*-----End of test---*" << std::endl;
	std::cout << "*-------------------*" << std::endl;

}

option::configuration ParseArguments(int argc, char** argv) {

	//assert(argc > 2);
	option::configuration config;


	for (int i = 1; i < argc; ++i) {
		auto argument = std::string(argv[i]);
		assert(!argument.empty());
		if (argument.at(0) == option::arg_start && (2 == argument.size())) {
			if (argument.at(1) == option::file) {
				assert(i + 1 < argc);
				config.file_path = argv[i + 1];
				++i;
			}
			else if (argument.at(1) == option::type) {

				assert(i + 1 < argc);
				std::string type = argv[i + 1];
				if (type == option::int_type)
					config.type_option = TypeOption::INT;
				else if (type == option::double_type)
					config.type_option = TypeOption::DOUBLE;

				assert(TypeOption::UNKNOWN != config.type_option);

				++i;
			}
			else if (argument.at(1) == option::range) {
				assert(i + 2 < argc);
				config.min = argv[i + 1];
				config.max = argv[i + 2];

				i += 2;
				assert(!config.min.empty());
				assert(!config.max.empty());
			}
			else
			{
				std::cout << "Unknown argument: " << argv[i] << std::endl;
			}
		}


	}

	return config;

}

