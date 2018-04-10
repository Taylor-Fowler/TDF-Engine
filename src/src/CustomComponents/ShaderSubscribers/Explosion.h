#pragma once
#include <memory>
#include "..\..\Engine\Components\Component.h"


class Material;


class Explosion : public Component
{
private:
	bool m_loop					= true;
	bool m_destroy				= false;
	bool m_useTime				= true;
	double m_explosionStart		= 0.0;
	double m_explosionDuration	= 5.0;
	double m_lastExplosion;

	std::shared_ptr<Material> m_material;
public:
	Explosion();

	void StartExplosion(double time);
	void ExplosionDuration(double time);
	void SetLoop(bool status);
	void SetDestroy(bool status);
	void UseTime(bool status)
	{
		m_useTime = status;
	}

protected:
	void Update() override;
	bool Initialise() override;
};