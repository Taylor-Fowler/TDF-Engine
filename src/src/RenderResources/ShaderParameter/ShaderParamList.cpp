#include "ShaderParamList.h"
#include "..\ShaderModule\ShaderModule.h"


ShaderParamList::ShaderParamList(std::shared_ptr<ShaderModule> shaderModule)
{
	m_subscribedTo = shaderModule;
	m_subscribedTo->Subscribe(std::shared_ptr<ShaderParamList>(this));
}

ShaderParamList::~ShaderParamList()
{
	m_subscribedTo->Unsubscribe(std::shared_ptr<ShaderParamList>(this));
}

bool ShaderParamList::AddParameter(const std::string & paramName, FloatData & data)
{
	// If the parameter already exists with the same type specified, replace it
	auto parameterLocation = m_allParams.find(paramName);
	if (parameterLocation != m_allParams.end())
	{
		if (parameterLocation->second == SHADER_PARAMETER_TYPE::SPT_FLOAT)
		{
			m_floatParams[paramName].reset(new FloatData(data));
			return true;
		}
		return false;
	}
	m_floatParams.insert(std::make_pair(paramName, std::make_unique<FloatData>(data)));
	return true;
}

bool ShaderParamList::AddParameter(const std::string & paramName, std::unique_ptr<FloatData> data)
{
	// If the parameter already exists with the same type specified, replace it
	auto parameterLocation = m_allParams.find(paramName);
	if (parameterLocation != m_allParams.end())
	{
		if (parameterLocation->second == SHADER_PARAMETER_TYPE::SPT_FLOAT)
		{
			delete m_floatParams[paramName].release();
			m_floatParams[paramName].swap(std::move(data));
			return true;
		}
		return false;
	}
	m_floatParams.insert(std::make_pair(paramName, std::move(data)));
	return true;
}

bool ShaderParamList::RemoveParameter(std::string paramName)
{
	auto parameterLocation = m_allParams.find(paramName);
	if (parameterLocation != m_allParams.end())
	{
		switch (parameterLocation->second)
		{
		case SPT_FLOAT:
			return m_floatParams.erase(paramName) != 0;
		case SPT_UINT:
			return m_uintParams.erase(paramName) != 0;
		case SPT_INT:
			return m_intParams.erase(paramName) != 0;
		case SPT_TEXTURE:
			return m_textureParams.erase(paramName) != 0;
		}
	}
	return false;
}

void ShaderParamList::Render(std::shared_ptr<Program>& program) const
{
	for (auto const &fParamPair : m_floatParams)
	{
		fParamPair.second->Render(program, fParamPair.first);
	}
	for (auto const &uiParamPair : m_uintParams)
	{
		uiParamPair.second->Render(program, uiParamPair.first);
	}
}
