#pragma once
#include <iostream>

class FileReadWrite
{
public:
	FileReadWrite() {};
	virtual ~FileReadWrite() = 0 {};

	bool FileExists(const std::string &file);
};