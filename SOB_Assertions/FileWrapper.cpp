#include "FileWrapper.h"

#include <vector>
//#define NDEBUG
#include <cassert>

FileWrapper::FileWrapper() : binary_mode{false} {}

FileWrapper::~FileWrapper() { Close(); }

bool FileWrapper::Open(const std::string file_name,
                       std::ios_base::openmode mode) {
  file.open(file_name, mode);

  if ((std::ios::binary | std::ios::in) == mode) {
    copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(),
         std::ostreambuf_iterator<char>(buffer));
    assert(!buffer.bad());
    binary_mode = true;
  } else
    binary_mode = false;

  return file.good();
}

bool FileWrapper::Close() {
  buffer.clear();
  if (file.is_open()) {
    file.close();
    return true;
  }
  return false;
}

std::string FileWrapper::ReadWord() {
  if (binary_mode) {
    std::string token;
    buffer >> token;
    return token;
  } else {
    std::string lane;
    if (!EndOfFile() && IsOk() && file >> lane) {
      return lane;
    }
  }
  return std::string();
}

std::vector<std::string> FileWrapper::ReadWordsToVector() {
  std::string number_str;

  std::vector<std::string> words;

  while (file >> number_str) {
    words.push_back(number_str);
  }
  return words;
}

bool FileWrapper::IsOk() { return binary_mode ? !buffer.fail() : !file.fail(); }

bool FileWrapper::EndOfFile() {
  return binary_mode ? buffer.eof() : file.eof();
}
