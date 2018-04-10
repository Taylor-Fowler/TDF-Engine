#pragma once
#include <string>
#include <memory>
#include <map>

#include "Mesh\Mesh.h"

// Resource objects
class Texture;


class ResourceManager
{
private:
	std::map<std::string, std::weak_ptr<Mesh>>		m_loadedMeshes;
	std::map<std::string, std::weak_ptr<Texture>>	m_loadedTextures;

public:
	ResourceManager() {};

	std::shared_ptr<Mesh> FindMesh(const std::string &name);
	bool AddMesh(const std::string &name, std::shared_ptr<Mesh>& mesh);

	std::shared_ptr<Texture> FindTexture(const std::string &name);
	bool AddTexture(const std::string &name, std::shared_ptr<Texture> texture);

};