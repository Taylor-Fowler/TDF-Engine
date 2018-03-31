#pragma once
#include <vector>
#include <memory>

class ShaderParamList;
class Camera;
class Program;

class ShaderModule
{
private:
	std::vector<std::shared_ptr<ShaderParamList>> m_moduleSubscribers;
protected:
	std::shared_ptr<Program> m_mainProgram;

public:
	ShaderModule(std::shared_ptr<Program> program);
	virtual ~ShaderModule() {};

	virtual void Render(Camera *const camera);
	void Subscribe(std::shared_ptr<ShaderParamList> params)
	{
		m_moduleSubscribers.push_back(params);
	};
	void Unsubscribe(std::shared_ptr<ShaderParamList> params);

};