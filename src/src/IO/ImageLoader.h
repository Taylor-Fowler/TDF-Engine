#pragma once
#include <string>

class ImageLoader
{
private:
	unsigned int m_imageID = 0;
public:
	ImageLoader();
	bool Load(const std::string filename, unsigned int format);
	unsigned int LoadedImageHeight();
	unsigned int LoadedImageWidth();
	void * LoadedImageBits();
};