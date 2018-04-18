#pragma once
#include "..\Component.h"
#include "..\Transform\Transform.h"
#include "..\..\..\RenderResources\Texture\CubeTexture.h"


class Camera : public Component, public IRender
{
	friend class GameObject;
	friend int main(int argc, char *argv[]);
public:
	glm::vec4	m_clearColour = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	float		m_nearPlane		= 0.02f;
	float		m_farPlane		= 1000.0f;
	float		m_fovDegrees	= 60.0f;

private:
	static std::vector<Camera*> _allCameras;
	static Camera* _mainCamera;

protected:
	Transform m_transform;

	glm::mat4 m_viewMatrix;
	glm::vec3 m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_rightDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 m_upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	const glm::vec3 DEFAULT_VIEW = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 DEFAULT_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 DEFAULT_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	std::shared_ptr<CubeTexture> m_skybox;

public:
	static Camera* const main();
	static std::vector<Camera*> AllCameras();

	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;

	void SetSkybox(std::shared_ptr<CubeTexture> skybox)
	{
		m_skybox = skybox;
	}

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

	glm::vec3 Forward()
	{
		return m_viewDirection;
	}
	glm::vec3 Up()
	{
		return DEFAULT_UP * glm::mat3(m_viewMatrix);
	}
	glm::vec3 Right()
	{
		return DEFAULT_RIGHT * glm::mat3(m_viewMatrix);
	}
	glm::mat4 ViewMatrix()
	{
		return m_viewMatrix;
	}
	glm::vec3 Position()
	{
		return m_transform.Position();
	}
	std::weak_ptr<CubeTexture> Skybox()
	{
		return m_skybox;
	}

private:
	Camera();
	~Camera();
	void buildViewDirection();
	void rebuildViewMatrix();

};