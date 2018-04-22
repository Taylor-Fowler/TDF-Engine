#pragma once
#include <memory>
#include "..\Engine\Components\Camera\Camera.h"
#include "..\Engine\EventSystem\EventSystem.h"
#include "..\Engine\EventSystem\EventInterfaces\IKeyboardEvents.h"

class Terrain;

class BasicCameraController : public Component
{
private:
	Camera			*m_camera			= nullptr;
	MousePosition	m_mouse				= { 0, 0 };
	bool			m_lmbDown			= false;
	bool			m_lmbDownPrevious	= false;
	Terrain			*m_terrain			= nullptr;
	float			m_speed				= 1.0f;
	glm::vec3		m_velocity			= { 0.0f, 0.0f, 0.0f };
	bool			m_jumping			= false;
	float			m_offset			= 7.0f;
	bool			m_freeRoam			= false;

public:
	BasicCameraController();
	void SetTerrain(Terrain * terrain);
private:
	void move();
	void processJump();
	void ground();

protected:
	void Update() override;


};