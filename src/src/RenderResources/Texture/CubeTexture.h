#pragma once
#include "Texture.h"

class CubeTexture : public Texture
{
protected:
	static unsigned int White_CubeTexture_ID;

public:
	CubeTexture(int width, int height)
		: Texture(width, height)
	{};

	~CubeTexture() override = 0 {};

	void Bind() const override = 0;
	void Unbind() const override = 0;
	virtual void BindFace(unsigned int i) const = 0;

protected:
	void initialiseWhiteTexture() override {};
};