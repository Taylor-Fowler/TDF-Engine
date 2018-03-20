#include "ResourceManager.h"


std::shared_ptr<Mesh> ResourceManager::FindMesh(const std::string &name)
{
	std::map<std::string, std::weak_ptr<Mesh>>::iterator it;
	
	it = m_loadedMeshes.find(name);
	// Found the mesh
	if (it != m_loadedMeshes.end())
	{
		// Check the weak ptr hasnt expired before returning as a shared
		if (!it->second.expired())
		{
			return it->second.lock();
		}
		// Weak pointer expired so remove it from the collection
		else
		{
			m_loadedMeshes.erase(it);
		}
	}

	return std::shared_ptr<Mesh>();
}

bool ResourceManager::AddMesh(const std::string & name, std::shared_ptr<Mesh>& mesh)
{
	// It already exists
	if (FindMesh(name) != nullptr)
		return false;

	m_loadedMeshes.emplace(std::pair<std::string, std::weak_ptr<Mesh>>(name, mesh));
	return true;
}

std::shared_ptr<Texture> ResourceManager::FindTexture(const std::string & name)
{
	std::map<std::string, std::weak_ptr<Texture>>::iterator it;

	it = m_loadedTextures.find(name);
	// Found the texture
	if (it != m_loadedTextures.end())
	{
		// Check the weak ptr hasnt expired before returning as a shared
		if (!it->second.expired())
		{
			return it->second.lock();
		}
		// Weak pointer expired so remove it from the collection
		else
		{
			m_loadedTextures.erase(it);
		}
	}
	return std::shared_ptr<Texture>();
}

bool ResourceManager::AddTexture(const std::string & name, std::shared_ptr<Texture>& texture)
{
	// It already exists
	if (FindTexture(name) != nullptr)
		return false;

	m_loadedTextures.emplace(std::pair<std::string, std::weak_ptr<Texture>>(name, texture));
	return true;
}


