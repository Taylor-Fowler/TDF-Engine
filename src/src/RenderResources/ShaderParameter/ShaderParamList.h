#pragma once
#include <vector>
#include <memory>

#include "ShaderParameters.h"
#include "glm\glm.hpp"

#include "..\IRender.h"

class ShaderModule;

class ShaderParamList : public IRender
{
private:
	std::map<std::string, std::unique_ptr<FloatData>> m_floatParams;
	std::map<std::string, std::unique_ptr<UintData>> m_uintParams;
	std::map<std::string, std::unique_ptr<IntData>> m_intParams;
	std::map<std::string, std::shared_ptr<Texture>> m_textureParams;

	std::map<std::string, SHADER_PARAMETER_TYPE> m_allParams;
protected:
	std::shared_ptr<ShaderModule> m_subscribedTo = nullptr;

public:
	ShaderParamList(std::shared_ptr<ShaderModule> shaderModule);
	~ShaderParamList();

	bool AddParameter(const std::string &paramName, FloatData &data);
	bool AddParameter(const std::string &paramName, std::unique_ptr<FloatData> data);
	bool AddParameter(const std::string &paramName, std::shared_ptr<Texture> data);

	bool RemoveParameter(std::string paramName);

	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;
	virtual std::shared_ptr<Texture> GetTexture(const std::string &paramName) const;
};