#pragma once
#include <vector>
#include <memory>
#include "glm\glm.hpp"
#include "..\IRender.h"

class ShaderParamList;
class Camera;
class Program;
class RenderResourceFactory;

class ShaderModule
{
	friend int main(int argc, char *argv[]);
protected:
	static RenderResourceFactory *				_renderResourceFactory;

	std::shared_ptr<Program> m_mainProgram;
	std::vector<ShaderParamList*> m_paramSubscribers;
	std::vector<IRender*> m_renderSubscribers;

public:
	ShaderModule(std::shared_ptr<Program> program);
	virtual ~ShaderModule() {};

	virtual void Render(RenderDetails renderDetails);
	virtual void Subscribe(ShaderParamList* params)
	{
		if(params != nullptr)
			m_paramSubscribers.push_back(params);
	};
	virtual void Subscribe(IRender* renderable)
	{
		if (renderable != nullptr)
			m_renderSubscribers.push_back(renderable);
	};

	virtual void Unsubscribe(ShaderParamList* params);
	virtual void Unsubscribe(IRender* renderable);

};