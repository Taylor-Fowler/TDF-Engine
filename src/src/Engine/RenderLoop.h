#pragma once
#include <string>
#include <map>
#include <memory>

#include "..\RenderResources\Program\Program.h"

// The render loop owns the programs and their modules, as soon as the module is removed from the render loop, the shader program and its references should be removed?

class ShaderModule;


class RenderLoop
{
	friend int main(int argc, char *argv[]);
private:
	std::shared_ptr<Program> m_defaultProgram;
	std::shared_ptr<ShaderModule> m_defaultModule;

	std::map<std::string, std::shared_ptr<Program>> m_programs;
public:
	RenderLoop() {};


	void RenderFrame();

	void AddProgram(std::shared_ptr<Program> program, const std::string& name);
	std::weak_ptr<Program> GetProgram(const std::string& programName) const;


	std::string NextValidProgramName(const std::string& name) const;
	std::shared_ptr<ShaderModule> DefaultShaderModule() const {
		return m_defaultModule;
	}
};