#ifndef FILE_WRAPPER_H
#define FILE_WRAPPER_H

#include "IFileWrapper.h"

class FileWrapper :	public IFileWrapper
{
	std::fstream file;
public:
	FileWrapper();
	~FileWrapper();



	// Inherited via IFileWrapper
	virtual bool Open(const std::string file_name, std::ios_base::openmode mode) override;

	virtual bool Close() override;

	virtual std::string ReadWord() override;

	virtual bool EndOfFile() override;

};

#endif