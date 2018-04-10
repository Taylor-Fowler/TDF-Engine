#pragma once
#include <string>

class ImageLoader
{
public:
	ImageLoader();
	void* Load(const std::string filename, unsigned int format, unsigned int &width, unsigned int &height);
};