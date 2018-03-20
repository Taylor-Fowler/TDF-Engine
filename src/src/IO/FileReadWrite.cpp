#include "FileReadWrite.h"
#include <fstream>

bool FileReadWrite::FileExists(const std::string &file)
{
	std::ifstream fin(file.c_str());

	if (fin.fail())
		return false;

	return true;
}
