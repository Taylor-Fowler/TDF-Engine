#pragma once
#include <vector>
#include <memory>

#include "ShaderParameters.h"
#include "../IRender.h"

class ShaderParamList : public IRender
{
private:
	std::map<std::string, std::unique_ptr<FloatData>> m_floatParams;
	std::map<std::string, std::unique_ptr<UintData>> m_uintParams;
	std::map<std::string, std::unique_ptr<IntData>> m_intParams;
	std::map<std::string, std::weak_ptr<Texture>> m_textureParams;

	std::map<std::string, SHADER_PARAMETER_TYPE> m_allParams;

public:
	~ShaderParamList() override {};

	bool AddParameter(const std::string &paramName, FloatData &data);
	bool AddParameter(const std::string &paramName, std::unique_ptr<FloatData> data);
	bool RemoveParameter(std::string paramName);

	void Render(std::shared_ptr<Program>& program) const override;
};