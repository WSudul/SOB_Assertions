/* SOB - lab 1*/

#include <iostream>
#include <memory>
#include <vector>

//#define NDEBUG
#include <cassert>

#include "FileWrapper.h"
#include "SortedLinkedList.h"

enum TypeOption { INT = 1, DOUBLE = 2, UNKNOWN = 99 };

namespace option {
constexpr auto arg_start = '-'; // starts each argument below
constexpr auto file =
    'f'; // path to file with data - needs to be followed by string
constexpr auto type = 't';        // type - tread data as inegers or doubles
constexpr auto range = 'r';       // range - needs to be followed by 2 numbers
constexpr auto binary_mode = 'b'; // optional - open as binary file

constexpr auto int_type = "int";
constexpr auto double_type = "double";

struct configuration {
  std::string file_path;
  std::ios_base::openmode mode = std::ios::in;
  TypeOption type_option = TypeOption::UNKNOWN;
  std::string min;
  std::string max;
};
} // namespace option

template <typename T>
void TestLinkedList(std::unique_ptr<SortedLinkedList<T>> &list);
void TestFileWrapper();

option::configuration ParseArguments(int argc, char **argv);
bool VerifyConfiguration(const option::configuration &config);

/*
example of arguments via console:
-f ../SOB_Assertions/resources/numbers.txt -r 0 5 -t double
*/

int main(int argc, char **argv) {
  option::configuration config;
  config = ParseArguments(argc, argv);
  bool configuration_valid = VerifyConfiguration(config);
  assert(configuration_valid);

  std::cout << config.file_path << "\t" << config.mode << "\t"
            << config.type_option << "\t" << config.min << "\t" << config.max
            << std::endl;

  std::unique_ptr<IFileWrapper> file_wrapper = std::make_unique<FileWrapper>();
  bool file_open_success = file_wrapper->Open(config.file_path, config.mode);
  assert(file_open_success);
  std::vector<std::string> words;
  while (!file_wrapper->EndOfFile()) {
    std::string word = file_wrapper->ReadWord();
    assert(file_wrapper->IsOk());

    if (!word.empty())
      words.push_back(word);
  }

  switch (config.type_option) {
  case TypeOption::INT: {
    std::unique_ptr<SortedLinkedList<int>> linked_list_int =
        std::make_unique<SortedLinkedList<int>>();
    try {
      int min = std::stoi(config.min);
      int max = std::stoi(config.max);
      std::cout << "Reading to integer linked list" << std::endl;
      for (auto &word : words) {
        int value = std::stoi(word);
        assert(value >= min && value <= max);
        linked_list_int->Add(value);
      }
    } catch (std::invalid_argument &e) {
      std::cout << "Exception caught while parsing data to selected type: "
                << e.what() << std::endl;
      return 0;
    }
    std::cout << "Printing integer linked list" << std::endl;
    std::cout << linked_list_int->ToString() << std::endl;
    ;
    std::cout << linked_list_int->ReversedToString() << std::endl;

  } break;
  case TypeOption::DOUBLE: {
    std::unique_ptr<SortedLinkedList<double>> linked_list_double =
        std::make_unique<SortedLinkedList<double>>();
    try {
      double min = std::stod(config.min);
      double max = std::stod(config.max);
      std::cout << "Reading to double linked list" << std::endl;
      for (auto &word : words) {
        double value = std::stod(word);
        assert(value >= min && value <= max);
        linked_list_double->Add(value);
      }
    } catch (std::invalid_argument &e) {
      std::cout << "Exception caught while parsing data to selected type: "
                << e.what() << std::endl;
      return 0;
    }
    std::cout << "Printing double linked list" << std::endl;
    std::cout << linked_list_double->ToString() << std::endl;
    ;
    std::cout << linked_list_double->ReversedToString() << std::endl;

  } break;
  default:
    std::cout << "Unsupported option activated" << std::endl;
  }

  // TESTING
  // std::unique_ptr<SortedLinkedList<int>> linked_list_int_customer_comparator
  // = std::make_unique<SortedLinkedList<int>>([](const int& v1, const int&v2)
  // {return v1 < v2; }); std::unique_ptr<SortedLinkedList<int>> linked_list_int
  // = std::make_unique<SortedLinkedList<int>>();
  // std::unique_ptr<SortedLinkedList<double>> linked_list_double =
  // std::make_unique<SortedLinkedList<double>>();
  // TestLinkedList(linked_list_double);
  // TestLinkedList(linked_list_int);
  // TestLinkedList(linked_list_int_customer_comparator);
  // TestFileWrapper();

  return 0;
}

template <typename T>
void TestLinkedList(std::unique_ptr<SortedLinkedList<T>> &list) {
  std::cout << "*---Start of test---*" << std::endl;
  bool test_add_success = true;
  test_add_success &= (list->isEmpty());
  test_add_success &= (list->Add(1));
  test_add_success &= (list->Add(2));
  test_add_success &= (list->Add(5));
  test_add_success &= (list->Add(3));
  test_add_success &= (list->Add(4));
  test_add_success &= (list->Add(2));
  test_add_success &= (6 == list->Size());
  assert(test_add_success);
  std::cout << list->ToString() << std::endl;
  std::cout << list->ReversedToString() << std::endl;

  std::cout << "-------------------" << std::endl;
  bool test_pop_success = true;
  test_pop_success &= (list->PopFront());
  test_pop_success &= (list->PopBack());
  test_pop_success &= (4 == list->Size());
  std::cout << list->ToString() << std::endl;
  std::cout << list->ReversedToString() << std::endl;
  std::cout << "-------------------" << std::endl;

  bool test_add_again_success = true;
  list->Clear();
  test_add_again_success &= (0 == list->Size());
  test_add_again_success &= (list->isEmpty());
  test_add_again_success &= (list->Add(2));
  test_add_again_success &= (list->Add(3));
  test_add_again_success &= (list->Add(5));
  test_add_again_success &= (list->Add(1));
  test_add_again_success &= (list->Add(4));
  test_add_again_success &= (list->Add(6));
  test_add_again_success &= (6 == list->Size());
  assert(test_add_again_success);
  std::cout << list->ToString() << std::endl;
  std::cout << list->ReversedToString() << std::endl;
  std::cout << "*-----End of test---*" << std::endl;
  std::cout << "*-------------------*" << std::endl;
}

void TestFileWrapper() {
  std::cout << "*---Start of test---*" << std::endl;
  std::cout << "*---File wrapper----*" << std::endl;
  std::unique_ptr<IFileWrapper> file_wrapper = std::make_unique<FileWrapper>();
  bool test_file_success = true;
  test_file_success &=
      (!file_wrapper->Open("dummy_non_existing_file.dummy", std::ios::in));
  test_file_success &= (!file_wrapper->Close());

  // open binary file and read some value
  test_file_success &=
      (file_wrapper->Open("../SOB_Assertions/resources/binary_file_test",
                          std::ios::in | std::ios::binary));
  test_file_success &= (file_wrapper->IsOk());
  test_file_success &= (!file_wrapper->EndOfFile());

  test_file_success &= ("112345" == file_wrapper->ReadWord());
  test_file_success &= ("444" == file_wrapper->ReadWord());
  test_file_success &= ("203" == file_wrapper->ReadWord());
  test_file_success &= ("3022" == file_wrapper->ReadWord());
  test_file_success &= ("-42" == file_wrapper->ReadWord());
  test_file_success &= ("0" == file_wrapper->ReadWord());
  test_file_success &= ("3.1415" == file_wrapper->ReadWord());
  test_file_success &= ("3e7" == file_wrapper->ReadWord());
  test_file_success &=
      ("" == file_wrapper->ReadWord()); // empty string after end of file
  test_file_success &= (file_wrapper->EndOfFile());
  test_file_success &= (file_wrapper->Close());

  assert(test_file_success);

  std::cout << file_wrapper->Open("../SOB_Assertions/resources/numbers.txt",
                                  std::ios::in)
            << std::endl;
  std::vector<std::string> words1 = file_wrapper->ReadWordsToVector();

  for (int i = 0; i < words1.size(); ++i)
    std::cout << words1[i] << ' ';
  file_wrapper->Close();

  std::cout << "*-----End of test---*" << std::endl;
  std::cout << "*-------------------*" << std::endl;
}

option::configuration ParseArguments(int argc, char **argv) {

  assert(argc > 2);
  option::configuration config;

  for (int i = 1; i < argc; ++i) {
    auto argument = std::string(argv[i]);
    assert(!argument.empty());
    if (argument.at(0) == option::arg_start && (2 == argument.size())) {
      if (argument.at(1) == option::file) {
        assert(i + 1 < argc);
        config.file_path = argv[i + 1];
        ++i;
      } else if (argument.at(1) == option::type) {

        assert(i + 1 < argc);
        std::string type = argv[i + 1];
        if (type == option::int_type)
          config.type_option = TypeOption::INT;
        else if (type == option::double_type)
          config.type_option = TypeOption::DOUBLE;

        assert(TypeOption::UNKNOWN != config.type_option);

        ++i;
      } else if (argument.at(1) == option::range) {
        assert(i + 2 < argc);
        config.min = argv[i + 1];
        config.max = argv[i + 2];

        assert(!config.min.empty());
        assert(!config.max.empty());

        i += 2;

      } else if (argument.at(1) == option::binary_mode) {

        config.mode |= std::ios::binary;
      } else {
        std::cout << "Unknown argument: " << argv[i] << std::endl;
      }
    }
  }

  return config;
}

bool VerifyConfiguration(const option::configuration &config) {

  // verify configuration
  assert(!config.file_path.empty());
  assert(0 != config.mode);
  assert(!config.min.empty());
  assert(!config.max.empty());
  assert(TypeOption::UNKNOWN != config.type_option);
  try {
    assert((std::stod(config.max) > std::stod(config.min)));
  } catch (std::invalid_argument &ex) {
    std::cout << "Exception caught: " << ex.what() << std::endl;
    return false;
  }
  return true;
}