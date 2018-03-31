#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Camera.h"
#include "..\..\..\RenderResources\Program\Program.h"

std::vector<Camera*> Camera::_allCameras;
Camera* Camera::_mainCamera = nullptr;

Camera::Camera()
{
	m_transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	if (_mainCamera == nullptr)
		_mainCamera = this;

	_allCameras.push_back(this);
}

Camera::~Camera()
{
	auto camera = std::find(_allCameras.begin(), _allCameras.end(), this);
	_allCameras.erase(camera);

	if (_mainCamera == this)
	{
		if (_allCameras.size() == 0)
			_mainCamera = nullptr;
		else
			_mainCamera = *_allCameras.begin();
	}
}

Camera * const Camera::main()
{
	return _mainCamera;
}

std::vector<Camera*> Camera::AllCameras()
{
	return _allCameras;
}

void Camera::Render(std::shared_ptr<Program>& program) const
{
	program->SendParam("viewMatrix", glm::value_ptr(m_viewMatrix));
}

void Camera::SetPosition(glm::vec3 newPosition)
{
	m_transform.SetPosition(newPosition);
	rebuildViewMatrix();
}

void Camera::SetPositionX(float newX)
{
	m_transform.SetPositionX(newX);
	rebuildViewMatrix();
}

void Camera::SetPositionY(float newY)
{
	m_transform.SetPositionY(newY);
	rebuildViewMatrix();
}

void Camera::SetPositionZ(float newZ)
{
	m_transform.SetPositionZ(newZ);
	rebuildViewMatrix();
}

void Camera::Translate(glm::vec3 translationVector)
{
	m_transform.Translate(translationVector);
	rebuildViewMatrix();
}

void Camera::SetRotation(glm::vec3 newRotation)
{
	m_transform.SetRotation(newRotation);
	m_viewDirection = glm::mat3(glm::rotate(glm::length(newRotation), glm::normalize(newRotation))) * DEFAULT_VIEW;
	m_rightDirection = glm::mat3(glm::rotate(glm::length(newRotation), glm::normalize(newRotation))) * DEFAULT_RIGHT;
	m_upDirection = glm::mat3(glm::rotate(glm::length(newRotation), glm::normalize(newRotation))) * DEFAULT_UP;
	rebuildViewMatrix();
}

void Camera::SetRotationX(float newX)
{
	m_transform.SetRotationX(newX);
	buildViewDirection();
	rebuildViewMatrix();
}

void Camera::SetRotationY(float newY)
{
	m_transform.SetRotationY(newY);
	buildViewDirection();
	rebuildViewMatrix();
}

void Camera::SetRotationZ(float newZ)
{
	m_transform.SetRotationZ(newZ);
	buildViewDirection();
	rebuildViewMatrix();
}

void Camera::Rotate(glm::vec3 rotation, float alpha)
{
	m_transform.Rotate(rotation, alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, rotation)) * m_viewDirection;
	m_rightDirection = glm::mat3(glm::rotate(alpha, rotation)) * m_rightDirection;
	m_upDirection = glm::mat3(glm::rotate(alpha, rotation)) * m_upDirection;
	rebuildViewMatrix();
}

void Camera::RotateX(float alpha)
{
	m_transform.RotateX(alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, m_transform.RIGHT)) * m_viewDirection;
	m_rightDirection = glm::mat3(glm::rotate(alpha, m_transform.RIGHT)) * m_rightDirection;
	m_upDirection = glm::mat3(glm::rotate(alpha, m_transform.RIGHT)) * m_upDirection;
	rebuildViewMatrix();
}

void Camera::RotateY(float alpha)
{
	m_transform.RotateY(alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, m_transform.UP)) * m_viewDirection;
	m_rightDirection = glm::mat3(glm::rotate(alpha, m_transform.UP)) * m_rightDirection;
	m_upDirection = glm::mat3(glm::rotate(alpha, m_transform.UP)) * m_upDirection;
	rebuildViewMatrix();
}

void Camera::RotateZ(float alpha)
{
	m_transform.RotateZ(alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, m_transform.FORWARD)) * m_viewDirection;
	m_rightDirection = glm::mat3(glm::rotate(alpha, m_transform.FORWARD)) * m_rightDirection;
	m_upDirection = glm::mat3(glm::rotate(alpha, m_transform.FORWARD)) * m_upDirection;
	rebuildViewMatrix();
}

void Camera::buildViewDirection()
{
	m_viewDirection = glm::mat3(glm::rotate(glm::length(m_transform.Rotation()), glm::normalize(m_transform.Rotation()))) * DEFAULT_VIEW;
	m_rightDirection = glm::mat3(glm::rotate(glm::length(m_transform.Rotation()), glm::normalize(m_transform.Rotation()))) * DEFAULT_RIGHT;
	m_upDirection = glm::mat3(glm::rotate(glm::length(m_transform.Rotation()), glm::normalize(m_transform.Rotation()))) * DEFAULT_UP;

}

void Camera::rebuildViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_transform.Position(), m_transform.Position() + m_viewDirection, m_transform.UP);
}
