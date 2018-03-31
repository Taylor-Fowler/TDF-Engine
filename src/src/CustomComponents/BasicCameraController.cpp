#include "BasicCameraController.h"

BasicCameraController::BasicCameraController()
{
	m_camera = Camera::main();
}

void BasicCameraController::Update()
{
	float speed = 0.01f;

	if (eventSystem()->IsKeyDown(ES_KEYC_W))
		m_camera->Translate(m_camera->Forward() * speed);
	if (eventSystem()->IsKeyDown(ES_KEYC_A))
		m_camera->Translate(m_camera->Right() * -speed);
	if (eventSystem()->IsKeyDown(ES_KEYC_S))
		m_camera->Translate(m_camera->Forward() * -speed);
	if (eventSystem()->IsKeyDown(ES_KEYC_D))
		m_camera->Translate(m_camera->Right() * speed);
	if (eventSystem()->IsKeyDown(ES_KEYC_Q))
		m_camera->Translate(m_camera->Up() * speed);
	if (eventSystem()->IsKeyDown(ES_KEYC_E))
		m_camera->Translate(m_camera->Up() * -speed);

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
