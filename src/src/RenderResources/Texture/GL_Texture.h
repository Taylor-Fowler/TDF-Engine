#pragma once
#include "Texture.h"


class GL_Texture : public Texture
{
public:
	GL_Texture();
	GL_Texture(int width, int height);
	GL_Texture(int width, int height, void* data);
	~GL_Texture();

	void Bind() const override;
	void Unbind() const override;

protected:
	void initialiseWhiteTexture() override;
	void init();
};