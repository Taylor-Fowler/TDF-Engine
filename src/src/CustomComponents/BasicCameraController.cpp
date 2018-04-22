#include "BasicCameraController.h"
#include "..\Engine\Components\Geometry\Terrain.h"

BasicCameraController::BasicCameraController()
{
	m_camera = Camera::main();
}

void BasicCameraController::SetTerrain(Terrain * terrain)
{
	if (terrain != nullptr)
	{
		m_terrain = terrain;
		m_camera->SetPosition({ 0.0f, m_terrain->GetHeight(0.0f, 0.0f) + m_offset, 0.0f });
	}
}

void BasicCameraController::move()
{
	if (eventSystem()->IsKeyDown(ES_KEYC_F))
		m_freeRoam = !m_freeRoam;

	if (!m_jumping || m_freeRoam)
	{
		glm::vec3 moveDirection = m_camera->Position();

		if (eventSystem()->IsKeyDown(ES_KEYC_W))
			m_camera->Translate(m_camera->Forward() * m_speed);
		if (eventSystem()->IsKeyDown(ES_KEYC_A))
			m_camera->Translate(m_camera->Right() * -m_speed);
		if (eventSystem()->IsKeyDown(ES_KEYC_S))
			m_camera->Translate(m_camera->Forward() * -m_speed);
		if (eventSystem()->IsKeyDown(ES_KEYC_D))
			m_camera->Translate(m_camera->Right() * m_speed);

		if (!m_freeRoam && eventSystem()->IsKeyDown(ES_KEYC_SPACE))
		{
			moveDirection = m_camera->Position() - moveDirection;
			moveDirection.y = 0.0f;
			if (moveDirection != glm::vec3(0.0f))
				moveDirection = glm::normalize(moveDirection);

			
			m_velocity = glm::vec3(0.0f, 0.4f, 0.0f) + moveDirection * m_speed * 0.5f;
			m_camera->Translate(glm::vec3(0.0f, 0.1f, 0.0f));
			m_jumping = true;
		}
	}
	//if (eventSystem()->IsKeyDown(ES_KEYC_Q))
	//	m_camera->Translate(m_camera->Up() * speed);
	//if (eventSystem()->IsKeyDown(ES_KEYC_E))
	//	m_camera->Translate(m_camera->Up() * -speed);
}

void BasicCameraController::processJump()
{
	if (!m_jumping) return;
	m_velocity.y -= 0.027f;
	m_camera->Translate(m_velocity);

	if (m_terrain != nullptr)
	{
		glm::vec3 pos = m_camera->Position();
		if (pos.y < m_terrain->GetHeight(pos.x, pos.z) + m_offset)
		{
			m_jumping = false;
			m_velocity = { 0.0f, 0.0f, 0.0f };
		}
	}

}

void BasicCameraController::ground()
{
	glm::vec3 pos = m_camera->Position();
	if (m_terrain != nullptr)
		m_camera->SetPositionY(m_terrain->GetHeight(pos.x, pos.z) + m_offset);
}

void BasicCameraController::Update()
{
	glm::vec3 pos = m_camera->Position();

	move();
	if (!m_freeRoam)
	{
		processJump();

		if (pos != m_camera->Position() && !m_jumping)
			ground();
	}


	

	// Only move the camera if the lmb is down
	if (m_lmbDown)
	{
		auto mouse = eventSystem()->GetMousePosition();
		auto change = MousePosition{ m_mouse.x - mouse.x, m_mouse.y - mouse.y };

		m_camera->Rotate(m_camera->Up(), change.x * 0.005f);
		m_camera->Rotate(m_camera->Right(), change.y * 0.005f);

		//m_camera->Rotate(glm::vec3(0, 1, 0), change.x * 0.005f);
		//m_camera->Rotate(glm::vec3(1, 0, 0), change.y * 0.005f);

		m_mouse = mouse;
	}

	if (!m_lmbDownPrevious)
		m_lmbDown = false;
	else
	{
		m_mouse = eventSystem()->GetMousePosition();
		m_lmbDown = eventSystem()->IsMouseBtnDown(ES_MOUSE_BTN_L);
	}
	
	m_lmbDownPrevious = eventSystem()->IsMouseBtnDown(ES_MOUSE_BTN_L);
}
