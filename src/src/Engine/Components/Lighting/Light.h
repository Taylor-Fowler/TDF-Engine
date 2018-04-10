#pragma once
#include "../Component.h"
#include "../../Maths/h/Vector3.h"


class Light : public Component
{
public:
	static const Vector3f	DEFAULT_DIFFUSE;
	static const Vector3f	DEFAULT_DIRECTION;
	static const double		DEFAULT_SHADOW_UPDATE_INTERVAL;

protected:
	// Lighting attributes
	Vector3f m_diffuse				= DEFAULT_DIFFUSE;

	// Light shadow attributes
	bool	m_shadowsEnabled		= false;
	double	m_lastShadowUpdate		= 0.0;
	double	m_shadowUpdateInterval	= DEFAULT_SHADOW_UPDATE_INTERVAL;

public:
	Light() {};
	virtual ~Light() {};

	virtual void SetShadowMatrix(float *shadow) = 0;

	void UpdatedShadow(double time);
	Vector3f& GetPosition();
	bool IsTimeToUpdate(double time);

	void SetDiffuse(const Vector3f& d)	{ m_diffuse = d; }
	void EnableShadows()				{ m_shadowsEnabled = true; }
	void DisableShadows()				{ m_shadowsEnabled = false; }
	void ToggleShadows()				{ m_shadowsEnabled = !m_shadowsEnabled; }


	Vector3f&	GetDiffuse()			{ return m_diffuse; }
	bool		IsShadowsEnabled()		{ return m_shadowsEnabled; }
	double		GetLastShadowUpdate()	{ return m_lastShadowUpdate; }



	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual bool Initialise() = 0;
};
