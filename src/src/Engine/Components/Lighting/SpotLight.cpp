#include "SpotLight.h"


SpotLight::SpotLight() : PointLight()
{
}

bool SpotLight::Initialise()
{
	m_depthFBC.Initialise(1600, 1200);
	return true;
}
