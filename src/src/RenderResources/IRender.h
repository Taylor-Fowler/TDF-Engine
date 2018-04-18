#pragma once
#include <memory>
#include "glm\glm.hpp"

// Forward declarations
class Program;
class Camera;

struct RenderDetails
{
	Camera		*renderingCamera;
	glm::mat4	viewMatrix;
	glm::mat4	transformMatrix;
	glm::mat4	projectionMatrix;
};

// Abstract class that requires all derivatives to implement the render function
class IRender
{
public:
	// All renderable objects must send their data to the shader program that they subscribed to
	virtual void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) = 0;

protected:
	virtual ~IRender() = 0 {};
};