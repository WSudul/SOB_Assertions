#include "FileWrapper.h"



FileWrapper::FileWrapper()
{
}


FileWrapper::~FileWrapper()
{
}

bool FileWrapper::Open(const std::string file_name, std::ios_base::openmode mode)
{
	return false;
}

bool FileWrapper::Close()
{
	return false;
}

std::string FileWrapper::ReadWord()
{
	return std::string{};
}

bool FileWrapper::EndOfFile()
{
	return false;
}
