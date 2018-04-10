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

	std::map<std::string, std::shared_ptr<ShaderModule>> m_modules;
	std::map<unsigned int, std::string> m_modulePositions;
	std::map<std::string, std::shared_ptr<Program>> m_programs;

	//struct lights_ubo
	//{
	//	const static int MAX_DIRECTIONAL_LIGHTS = 10;
	//	const static int MAX_POINT_LIGHTS = 10;
	//	const static int MAX_SPOT_LIGHTS = 10;

	//	struct directional_light
	//	{
	//		int On;
	//		float Direction[3];
	//		float Diffuse[3];
	//	} DirectionalLights[MAX_DIRECTIONAL_LIGHTS];

	//	struct point_light
	//	{
	//		int On;
	//		float Position[3];
	//		float Diffuse[3];
	//		float Specular[3];
	//	} PointLights[MAX_POINT_LIGHTS];

	//	struct spot_light
	//	{
	//		int On;
	//		float Position[3];
	//		float Specular[3];
	//		float Direction[3];
	//		float Cutoff;
	//		float Attenuation;
	//	} SpotLights[MAX_SPOT_LIGHTS];
	//} m_lights;

	//unsigned int m_ubo;
public:
	void RenderFrame();

	void AddProgram(std::shared_ptr<Program> program, const std::string& name);
	std::weak_ptr<Program> GetProgram(const std::string& programName) const;

	void AddModule(std::shared_ptr<ShaderModule> shaderModule, unsigned int position, const std::string& name);
	std::weak_ptr<ShaderModule> GetModule(const std::string& programName) const;

	std::string NextValidProgramName(const std::string& name) const;
	std::shared_ptr<ShaderModule> DefaultShaderModule() const {
		return m_defaultModule;
	}

private:
	void initialise();
};