#pragma once
#include "CubeTexture.h"


class GL_CubeTexture : public CubeTexture
{
public:
	GL_CubeTexture(int width, int height);
	GL_CubeTexture(int width, int height, void *x_pos, void *x_neg, void *y_pos, void *y_neg, void *z_pos, void *z_neg);
	~GL_CubeTexture() override;

	void Bind() const override;
	void Unbind() const override;
	void BindFace(unsigned int face) const override;
};