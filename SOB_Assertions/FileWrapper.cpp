#include "FileWrapper.h"



FileWrapper::FileWrapper()
{
	
}


FileWrapper::~FileWrapper()
{
}

bool FileWrapper::Open(const std::string file_name, std::ios_base::openmode mode)
{
	file.open(file_name, mode);
	std::string line;

	if (file.good())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FileWrapper::Close()
{
	if (file.is_open())
	{
		file.close();
		return true;
	}
	return false;
}

std::string FileWrapper::ReadWord()
{
	std::string lane;
	if (!EndOfFile() && getline(file, lane))
	{
		return lane;
	}
	return "Koniec pliku";
}

bool FileWrapper::EndOfFile()
{
	return file.eof();
}
