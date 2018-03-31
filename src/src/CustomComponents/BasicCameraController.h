#pragma once
#include <memory>
#include "..\Engine\Components\Camera\Camera.h"
#include "..\Engine\EventSystem\EventSystem.h"
#include "..\Engine\EventSystem\EventInterfaces\IKeyboardEvents.h"



class BasicCameraController : public Component
{
private:
	Camera * m_camera = nullptr;
	MousePosition m_mouse = { 0, 0 };
	bool m_lmbDown = false;
	bool m_lmbDownPrevious = false;

public:
	BasicCameraController();

protected:
	void Update() override;


};