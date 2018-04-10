#include "GL\glew.h"

#include "GL_Texture.h"

GL_Texture::GL_Texture()
	: Texture(1, 1)
{
	if (White_Texture_ID == 0)
		initialiseWhiteTexture();

	m_textureID = White_Texture_ID;
}


GL_Texture::GL_Texture(int width, int height)
	: Texture(width, height)
{
	init();
	glBindTexture(GL_TEXTURE_2D, 0);
}

GL_Texture::GL_Texture(int width, int height, void * data)
	: Texture(width, height)
{
	init();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

GL_Texture::~GL_Texture()
{
}

void GL_Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void GL_Texture::initialiseWhiteTexture()
{
	static unsigned char bytes[] = { 255, 255, 255 };

	glGenTextures(1, &White_Texture_ID);
	glBindTexture(GL_TEXTURE_2D, White_Texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_BGR, GL_UNSIGNED_BYTE, &bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL_Texture::init()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
