#pragma once


class Texture
{
protected:
	unsigned int		m_textureID;
	int					m_width;
	int					m_height;
	static unsigned int White_Texture_ID;
	

public:
	Texture(int width, int height)
		: m_width(width), m_height(height)
	{};
	virtual ~Texture() = 0 {};

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;


	unsigned int ID() const
	{
		return m_textureID;
	}

protected:
	virtual void initialiseWhiteTexture() = 0;


};