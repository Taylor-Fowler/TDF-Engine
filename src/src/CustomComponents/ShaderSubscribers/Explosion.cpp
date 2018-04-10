#include "Explosion.h"
#include "..\..\Engine\RenderLoop.h"
#include "..\..\Engine\GameObject\GameObject.h"
#include "..\..\RenderResources\Material\Material.h"
#include "..\..\RenderResources\ShaderModule\ShaderModule.h"
#include "..\..\RenderResources\Factory\RenderResourceFactory.h"


Explosion::Explosion()
{
	m_material = std::make_shared<Material>(_renderLoop->GetModule("Explosion").lock());
	m_material->AddParameter("explosionElapsed", std::move(std::make_unique<FloatData>((float)m_explosionStart)));
	m_material->AddParameter("texture0", _renderResourceFactory->LoadStaticTexture("Assets/Textures/Rock.png"));
	m_material->AddParameter("ambientMaterial", std::move(std::make_unique<FloatData3>(1.0f, 1.0f, 1.0f)));
}

void Explosion::Update()
{
	double time = AppTime::GetTime();
	double explosionTime;
	// 6 seconds between explosions
	if (m_lastExplosion + 6.0 < time)
	{
		if (m_explosionStart == m_lastExplosion - m_explosionDuration)
		{
			m_explosionStart = time;
		}

		explosionTime = time - m_explosionStart;
		if (explosionTime >= m_explosionDuration)
		{
			explosionTime = 0;
			m_lastExplosion = m_explosionStart + m_explosionDuration;
		}
	}
	else
	{
		explosionTime = 0.0;
	}


	double actualTime = (explosionTime > m_explosionDuration * 0.5) ? m_explosionDuration - explosionTime : explosionTime;

	m_material->AddParameter("explosionElapsed", std::move(std::make_unique<FloatData>((float)actualTime)));
}

bool Explosion::Initialise()
{
	m_objectAttachedTo->GetRenderer()->AddMaterial(m_material);
	return true;
}