#pragma once
#include "glm\glm.hpp"


#include "..\..\..\RenderResources\IRender.h"


class Transform : IRender
{
public:
	const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);
protected:
	glm::vec3 m_position	= glm::vec3(0.0f);
	glm::vec3 m_rotation	= glm::vec3(0.0f);
	glm::vec3 m_scale		= glm::vec3(1.0f);

	glm::mat4 m_transformMatrix;

public:
	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;

	void SetPosition(glm::vec3 newPosition);
	void SetPositionX(float newX);
	void SetPositionY(float newY);
	void SetPositionZ(float newZ);
	void Translate(glm::vec3 translationVector);

	void SetRotation(glm::vec3 newRotation);
	void SetRotationX(float newX);
	void SetRotationY(float newY);
	void SetRotationZ(float newZ);
	void Rotate(glm::vec3 rotation, float alpha);
	void RotateX(float alpha);
	void RotateY(float alpha);
	void RotateZ(float alpha);


	void SetScale(glm::vec3 newScale);
	void SetScaleX(float newX);
	void SetScaleY(float newY);
	void SetScaleZ(float newZ);
	void IncrementScale(glm::vec3 adjust);
	void AdjustScaleX(float adjustX);
	void AdjustScaleY(float adjustY);
	void AdjustScaleZ(float adjustZ);

	glm::vec3 Position()
	{
		return m_position;
	}
	glm::vec3 Rotation()
	{
		return m_rotation;
	}
	glm::vec3 Scale()
	{
		return m_scale;
	}
	glm::mat4 Matrix()
	{
		return m_transformMatrix;
	}

private:
	virtual void rebuildTransformMatrix();
};