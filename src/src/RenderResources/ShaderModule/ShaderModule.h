#pragma once
#include <vector>
#include <memory>
#include "glm\glm.hpp"

class ShaderParamList;
class Camera;
class Program;
class IRender;

class ShaderModule
{
private:
	std::vector<ShaderParamList*> m_paramSubscribers;
	std::vector<IRender*> m_renderSubscribers;
protected:
	std::shared_ptr<Program> m_mainProgram;

public:
	ShaderModule(std::shared_ptr<Program> program);
	virtual ~ShaderModule() {};

	virtual void PreRender(Camera *const camera);
	virtual void Render(const glm::mat4& viewMatrix);
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
private:
	virtual void init();
};