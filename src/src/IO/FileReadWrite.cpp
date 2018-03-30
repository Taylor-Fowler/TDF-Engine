#include "FileReadWrite.h"
#include <fstream>

bool FileReadWrite::FileExists(const std::string &file)
{
	std::ifstream fin(file.c_str());

	if (fin.fail())
		return false;

	return true;
}

std::string FileReadWrite::ImportTextFile(const std::string & file)
{
	std::ifstream buffer(file);
	std::string source(std::istreambuf_iterator<char>(buffer), (std::istreambuf_iterator<char>()));
	// TODO: Throw Exception?
	//if(source.empty()) 
	//		return nullptr;

	return source;
}
