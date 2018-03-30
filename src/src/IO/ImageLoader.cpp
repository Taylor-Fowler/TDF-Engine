#include "il.h"

#include "ImageLoader.h"


ImageLoader::ImageLoader()
{
	ilInit();
}

bool ImageLoader::Load(const std::string filename, unsigned int format)
{
	if (m_imageID != 0)
		ilDeleteImages(1, &m_imageID);

	ilGenImages(1, &m_imageID);
	ilBindImage(m_imageID);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	if (ilLoadImage(filename.c_str()))
	{
		ilConvertImage(format, IL_UNSIGNED_BYTE);
		return true;
	}
	return false;
}

unsigned int ImageLoader::LoadedImageHeight()
{
	if (m_imageID != 0)
		return ilGetInteger(IL_IMAGE_HEIGHT);
	return 0;
}

unsigned int ImageLoader::LoadedImageWidth()
{
	if (m_imageID != 0)
		return ilGetInteger(IL_IMAGE_WIDTH);
	return 0;
}

void * ImageLoader::LoadedImageBits()
{
	if (m_imageID != 0)
		return ilGetData();
	return 0;
}
