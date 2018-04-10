#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "glm\gtx\transform.hpp"

#include "Transform.h"
#include "..\..\..\RenderResources\Program\Program.h"

void Transform::Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails)
{
	program->SendParam("goTransformMatrix", glm::value_ptr(m_transformMatrix));
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	m_position = newPosition;
	rebuildTransformMatrix();
}

void Transform::SetPositionX(float newX)
{
	m_position.x = newX;
	rebuildTransformMatrix();
}

void Transform::SetPositionY(float newY)
{
	m_position.y = newY;
	rebuildTransformMatrix();
}

void Transform::SetPositionZ(float newZ)
{
	m_position.z = newZ;
	rebuildTransformMatrix();
}

void Transform::Translate(glm::vec3 translationVector)
{
	m_position += translationVector;
	rebuildTransformMatrix();
}

void Transform::SetRotation(glm::vec3 newRotation)
{
	m_rotation = newRotation;
	rebuildTransformMatrix();
}

void Transform::SetRotationX(float newX)
{
	m_rotation.x = newX;
	rebuildTransformMatrix();
}

void Transform::SetRotationY(float newY)
{
	m_rotation.y = newY;
	rebuildTransformMatrix();
}

void Transform::SetRotationZ(float newZ)
{
	m_rotation.z = newZ;
	rebuildTransformMatrix();
}

void Transform::Rotate(glm::vec3 rotation, float alpha)
{
	m_rotation = glm::rotate(m_rotation, alpha, rotation);
	rebuildTransformMatrix();
}

void Transform::RotateX(float alpha)
{
	m_rotation = glm::rotate(m_rotation, alpha, glm::vec3(0.0f, 1.0f, 0.0f));
	rebuildTransformMatrix();
}

void Transform::RotateY(float alpha)
{
	rebuildTransformMatrix();
}

void Transform::RotateZ(float alpha)
{
	rebuildTransformMatrix();
}

void Transform::SetScale(glm::vec3 newScale)
{
	m_scale = newScale;
	rebuildTransformMatrix();
}

void Transform::SetScaleX(float newX)
{
	rebuildTransformMatrix();
}

void Transform::SetScaleY(float newY)
{
	rebuildTransformMatrix();
}

void Transform::SetScaleZ(float newZ)
{
	rebuildTransformMatrix();
}

void Transform::IncrementScale(glm::vec3 adjust)
{
	rebuildTransformMatrix();
}

void Transform::AdjustScaleX(float adjustX)
{
	rebuildTransformMatrix();
}

void Transform::AdjustScaleY(float adjustY)
{
	rebuildTransformMatrix();
}

void Transform::AdjustScaleZ(float adjustZ)
{
	rebuildTransformMatrix();
}

void Transform::rebuildTransformMatrix()
{
	if (m_rotation == glm::vec3(0.0f))
	{
		m_transformMatrix = glm::translate(m_position) * glm::scale(m_scale);
	}
	else
	{
		m_transformMatrix = glm::translate(m_position) * glm::rotate(glm::length(m_rotation), glm::normalize(m_rotation)) * glm::scale(m_scale);
	}
}
