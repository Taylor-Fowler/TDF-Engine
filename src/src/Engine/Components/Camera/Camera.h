#pragma once
#include "..\Transform\Transform.h"

class Camera : IRender
{
protected:
	Transform m_transform;

	glm::mat4 m_viewMatrix;
	glm::vec3 m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	const glm::vec3 DEFAULT_VIEW = glm::vec3(0.0f, 0.0f, -1.0f);
public:
	Camera();
	void Render(std::shared_ptr<Program>& program) const override;

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


private:
	void buildViewDirection();
	void rebuildViewMatrix();

};