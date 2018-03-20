#pragma once
#include <memory>

// Forward declarations
class Program;

// Abstract class that requires all derivatives to implement the render function
class IRender
{
public:
	// All renderable objects must send their data to the shader program that they subscribed to
	virtual void Render(std::shared_ptr<Program>& program) const = 0;

protected:
	virtual ~IRender() = 0 {};
};