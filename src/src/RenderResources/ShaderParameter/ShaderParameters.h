#pragma once
#include <string>
#include <map>


#include "../Program/Program.h"
#include "../Texture/Texture.h"

//struct FloatData	{};
//struct UintData		{};
//struct IntData		{};

enum SHADER_PARAMETER_TYPE { SPT_FLOAT, SPT_UINT, SPT_INT, SPT_TEXTURE };

//using FloatParameter = std::pair<std::string, FloatData*>;
//using UintParameter = std::pair<std::string, UintData*>;
//using IntParameter = std::pair<std::string, IntData*>;
//using TextureParameter = std::pair<std::string, std::weak_ptr<Texture>>;



struct FloatData
{
protected:
	std::vector<float> data;
public:
	FloatData(float v0)
	{
		data.push_back(v0);
	}

	std::vector<float> Data()
	{
		return data;
	}

	virtual void Render(std::shared_ptr<Program>& program, const std::string &paramName) const
	{
		program->SendParam(paramName, data[0]);
	}
};

struct FloatData2 : public FloatData
{
public:
	FloatData2(float v0, float v1)
		: FloatData(v0)
	{
		data.push_back(v1);
	}

	void Render(std::shared_ptr<Program>& program, const std::string &paramName) const override
	{
		program->SendParam(paramName, data[0], data[1]);
	}
};

struct FloatData3 : public FloatData2
{
public:
	FloatData3(float v0, float v1, float v2)
		: FloatData2(v0, v1)
	{
		data.push_back(v2);
	}

	void Render(std::shared_ptr<Program>& program, const std::string &paramName) const override
	{
		program->SendParam(paramName, data[0], data[1], data[2]);
	}
};

struct FloatData4 : public FloatData3
{
public:
	FloatData4(float v0, float v1, float v2, float v3)
		: FloatData3(v0, v1, v2)
	{
		data.push_back(v3);
	}

	void Render(std::shared_ptr<Program>& program, const std::string &paramName) const override
	{
		program->SendParam(paramName, data[0], data[1], data[2], data[3]);
	}
};

struct FloatData16 : FloatData4
{
private:
	float arr[16];
public:
	FloatData16(float v0[16])
		: FloatData4(v0[0], v0[1], v0[2], v0[3])
	{
		for(int i = 4; i < 16; i ++)
			data.push_back(v0[i]);

		std::copy(data.begin(), data.end(), arr);
	}

	void Render(std::shared_ptr<Program>& program, const std::string &paramName) const override
	{
		program->SendParam(paramName, arr);
	}
};

struct UintData
{
protected:
	std::vector<unsigned int> data;
public:
	UintData(unsigned int v0)
	{
		data.push_back(v0);
	}

	virtual void Render(std::shared_ptr<Program>& program, const std::string &paramName) const
	{
		program->SendParam(paramName, data[0]);
	}
};



struct IntData
{
protected:
	std::vector<int> data;
public:
	IntData(int v0)
	{
		data.push_back(v0);
	}

	virtual void Render(std::shared_ptr<Program>& program, const std::string &paramName) const
	{
		program->SendParam(paramName, data[0]);
	}
};


//
//template <typename T>
//struct ShaderParameter : public IRender
//{
//protected:
//	std::pair<std::string, std::vector<T>> m_param;
//
//public:
//	void Render(std::shared_ptr<Program>& program) const override = 0;
//
//	std::string First() const { return m_param.first; }
//	std::vector<T> Second() const { return m_param.second; }
//
//	~ShaderParameter() override {};
//protected:
//	ShaderParameter() {};
//};
//
//struct FloatParam1 : public ShaderParameter<float>
//{
//	FloatParam1(float v0)
//	{
//		m_param.second.push_back(v0);
//	}
//	void Render(std::shared_ptr<Program>& program) const override
//	{
//		program->SendParam(m_param.first, m_param.second[0]);
//	}
//};
//
//struct FloatParam2 : public ShaderParameter<float>
//{
//	FloatParam2(float v0, float v1)
//	{
//		m_param.second.push_back(v0);
//		m_param.second.push_back(v1);
//	}
//	void Render(std::shared_ptr<Program>& program) const override
//	{
//		program->SendParam(m_param.first, m_param.second[0], m_param.second[1]);
//	}
//};
//
//struct FloatParam3 : public ShaderParameter<float>
//{
//	FloatParam3(float v0, float v1, float v2)
//	{
//		m_param.second.push_back(v0);
//		m_param.second.push_back(v1);
//		m_param.second.push_back(v2);
//	}
//	void Render(std::shared_ptr<Program>& program) const override
//	{
//		program->SendParam(m_param.first, m_param.second[0], m_param.second[1], m_param.second[2]);
//	}
//};


//template <unsigned int n, unsigned int nn>
//struct FloatParam : public IRender
//{
//	float		m_params[n * nn];
//	std::string m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params, nn, n);
//	}
//
//	~FloatParam() {};
//};
//
//template
//struct FloatParam<1U, 1U> : public IRender
//{
//	float		m_params[1U];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override	{
//		program->SendParam(m_paramName, m_params[0]);
//	}
//
//	~FloatParam<1, 1>() {}
//};
//
//template
//struct FloatParam<1U, 2U> : public IRender
//{
//	float		m_params[2U];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1]);
//	}
//};
//
//template
//struct FloatParam<1, 3> : public IRender
//{
//	float		m_params[3];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2]);
//	}
//};
//
//template
//struct FloatParam<1, 4> : public IRender
//{
//	float		m_params[4];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2], m_params[3]);
//	}
//};
//
//template <unsigned int n, unsigned int nn>
//struct IntParam : public IRender
//{
//	int			m_params[n * nn];
//	std::string m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params, nn, n);
//	}
//};
//
//template
//struct IntParam<1, 1> : public IRender
//{
//	int			m_params[1];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0]);
//	}
//};
//
//template
//struct IntParam<1, 2> : public IRender
//{
//	int			m_params[2];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1]);
//	}
//};
//
//template
//struct IntParam<1, 3> : public IRender
//{
//	int			m_params[3];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2]);
//	}
//};
//
//template
//struct IntParam<1, 4> : public IRender
//{
//	int			m_params[4];
//	std::string	m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2], m_params[3]);
//	}
//};
//
//
//template <unsigned int n, unsigned int nn>
//struct UIntParam : public IRender
//{
//	unsigned int	m_params[n * nn];
//	std::string		m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params, nn, n);
//	}
//};
//
//template
//struct UIntParam<1, 1> : public IRender
//{
//	unsigned int	m_params[1];
//	std::string		m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0]);
//	}
//};
//
//template
//struct UIntParam<1, 2> : public IRender
//{
//	unsigned int	m_params[2];
//	std::string		m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1]);
//	}
//};
//
//template
//struct UIntParam<1, 3> : public IRender
//{
//	unsigned int	m_params[3];
//	std::string		m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2]);
//	}
//};
//
//template
//struct UIntParam<1, 4> : public IRender
//{
//	unsigned int	m_params[4];
//	std::string		m_paramName;
//
//	void Render(std::shared_ptr<Program>& program) const override {
//		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2], m_params[3]);
//	}
//};
//



