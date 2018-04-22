#ifndef I_FILE_WRAPPER_H
#define I_FILE_WRAPPER_H

#include <string>
#include <fstream>


class IFileWrapper {
public:
	virtual ~IFileWrapper(){};
	virtual bool Open(const std::string file_name, std::ios_base::openmode mode) = 0;
	virtual bool Close() = 0;
	virtual std::string ReadWord( ) = 0;
	virtual bool IsOk() = 0;
	virtual bool EndOfFile() = 0;

};

#endif // !I_FILE_WRAPPER_H
