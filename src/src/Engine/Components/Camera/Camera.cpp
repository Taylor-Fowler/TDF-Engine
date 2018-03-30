#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Camera.h"
#include "..\..\..\RenderResources\Program\Program.h"

Camera::Camera()
{
	m_transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
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

	rebuildViewMatrix();
}

void Camera::RotateX(float alpha)
{
	m_transform.RotateX(alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, m_transform.RIGHT)) * m_viewDirection;
	rebuildViewMatrix();
}

void Camera::RotateY(float alpha)
{
	m_transform.RotateY(alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, m_transform.UP)) * m_viewDirection;
	rebuildViewMatrix();
}

void Camera::RotateZ(float alpha)
{
	m_transform.RotateZ(alpha);
	m_viewDirection = glm::mat3(glm::rotate(alpha, m_transform.FORWARD)) * m_viewDirection;
	rebuildViewMatrix();
}

void Camera::buildViewDirection()
{
	m_viewDirection = glm::mat3(glm::rotate(glm::length(m_transform.Rotation()), glm::normalize(m_transform.Rotation()))) * DEFAULT_VIEW;
}

void Camera::rebuildViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_transform.Position(), m_transform.Position() + m_viewDirection, m_transform.UP);
}
