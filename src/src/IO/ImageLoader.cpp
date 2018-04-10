#include "il.h"

#include "ImageLoader.h"


ImageLoader::ImageLoader()
{
	ilInit();
}

void* ImageLoader::Load(const std::string filename, unsigned int format, unsigned int &width, unsigned int &height)
{
	//http://wiki.ogre3d.org/OpenGL+Image+Loader+Using+DevIL+Image+Library
	ILuint image;

	ilGenImages(1, &image);
	ilBindImage(image);

	ILenum Error;
	Error = ilGetError();
	if (Error != IL_NO_ERROR)
		image = 2;

	//ilEnable(IL_ORIGIN_SET);
	//ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	if (ilLoadImage(filename.c_str()))
	{
		ilConvertImage(format, IL_UNSIGNED_BYTE);
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		return ilGetData();
	}
	return 0;
}

