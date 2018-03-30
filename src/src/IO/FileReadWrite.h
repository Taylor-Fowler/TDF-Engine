#pragma once
#include <iostream>

class FileReadWrite
{
public:
	FileReadWrite() {};
	virtual ~FileReadWrite() = 0 {};

	bool FileExists(const std::string &file);
	std::string ImportTextFile(const std::string &file);
};