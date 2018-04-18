#include "GL_CubeTexture.h"

#include "GL\glew.h"

GL_CubeTexture::GL_CubeTexture(int width, int height)
	: CubeTexture(width, height)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

GL_CubeTexture::GL_CubeTexture(int width, int height, void * x_pos, void * x_neg, void * y_pos, void * y_neg, void * z_pos, void * z_neg)
	: GL_CubeTexture(width, height)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, x_pos);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, x_neg);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, y_pos);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, y_neg);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, z_pos);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, z_neg);
	Unbind();	
}

GL_CubeTexture::~GL_CubeTexture()
{
	glDeleteTextures(1, &m_textureID);
}

void GL_CubeTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
}

void GL_CubeTexture::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void GL_CubeTexture::BindFace(unsigned int face) const
{
}
