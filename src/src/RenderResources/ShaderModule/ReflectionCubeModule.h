//#pragma once
//#include <map>
//#include "ShaderModule.h"
//
//class Framebuffer;
//class Material;
//
//class ReflectionCubeModule : public ShaderModule
//{
//private:
//	std::map<std::shared_ptr<Material>, std::unique_ptr<Framebuffer>> m_subscriberBuffers;
//
//public:
//	ReflectionCubeModule(std::shared_ptr<Program> program) : ShaderModule(program) {};
//	~ReflectionCubeModule() override {};
//
//	void PreRender(Camera *const camera) override;
//	void Render(const glm::mat4& viewMatrix) override;
//	void Subscribe(std::shared_ptr<ShaderParamList> params) override;
//	void Unsubscribe(std::shared_ptr<ShaderParamList> params) override;
//};