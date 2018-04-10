#pragma once
#include <memory>

class Texture;

class Framebuffer
{
protected:
	unsigned int m_framebufferID;
	std::shared_ptr<Texture> m_depthTexture;
	std::shared_ptr<Texture> m_colourTexture;

public:

	virtual ~Framebuffer() = 0 {};
};