#pragma once
#include <string>

#include "../IRender.h"
#include "../Program/Program.h"

template <unsigned int n, unsigned int nn>
struct FloatParam : public IRender
{
	float		m_params[n * nn];
	std::string m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params, nn, n);
	}

	~FloatParam() {};
};

template
struct FloatParam<1U, 1U> : public IRender
{
	float		m_params[1U];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override	{
		program->SendParam(m_paramName, m_params[0]);
	}

	~FloatParam<1, 1>() {}
};

template
struct FloatParam<1U, 2U> : public IRender
{
	float		m_params[2U];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1]);
	}
};

template
struct FloatParam<1, 3> : public IRender
{
	float		m_params[3];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2]);
	}
};

template
struct FloatParam<1, 4> : public IRender
{
	float		m_params[4];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2], m_params[3]);
	}
};

template <unsigned int n, unsigned int nn>
struct IntParam : public IRender
{
	int			m_params[n * nn];
	std::string m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params, nn, n);
	}
};

template
struct IntParam<1, 1> : public IRender
{
	int			m_params[1];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0]);
	}
};

template
struct IntParam<1, 2> : public IRender
{
	int			m_params[2];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1]);
	}
};

template
struct IntParam<1, 3> : public IRender
{
	int			m_params[3];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2]);
	}
};

template
struct IntParam<1, 4> : public IRender
{
	int			m_params[4];
	std::string	m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2], m_params[3]);
	}
};


template <unsigned int n, unsigned int nn>
struct UIntParam : public IRender
{
	unsigned int	m_params[n * nn];
	std::string		m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params, nn, n);
	}
};

template
struct UIntParam<1, 1> : public IRender
{
	unsigned int	m_params[1];
	std::string		m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0]);
	}
};

template
struct UIntParam<1, 2> : public IRender
{
	unsigned int	m_params[2];
	std::string		m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1]);
	}
};

template
struct UIntParam<1, 3> : public IRender
{
	unsigned int	m_params[3];
	std::string		m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2]);
	}
};

template
struct UIntParam<1, 4> : public IRender
{
	unsigned int	m_params[4];
	std::string		m_paramName;

	void Render(std::shared_ptr<Program>& program) const override {
		program->SendParam(m_paramName, m_params[0], m_params[1], m_params[2], m_params[3]);
	}
};




