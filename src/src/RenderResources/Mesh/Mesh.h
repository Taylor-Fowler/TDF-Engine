#pragma once
#include <string>
#include <memory>
#include <vector>

#include "glm\mat4x4.hpp"
#include "..\IRender.h"

class Loader3D;
class MeshBuilder;

struct Mesh_Data
{
	std::string							m_name;
	std::vector<float>					m_vertices;
	std::vector<float>					m_normals;
	std::vector<unsigned int>			m_indices;
	std::vector<float>					m_textureCoordinates;

	// TODO: This should be moved to a derivative structure that is specific to OpenGL
	// There is also the argument of having VBO's as structure where the ID maps to the vertex attribute...
	// but havent decided on that yet
	unsigned int						m_vaoID					= 0;
	unsigned int						m_verticesID			= 0;
	unsigned int						m_normalsID				= 0;
	unsigned int						m_indicesID				= 0;
	unsigned int						m_textureCoordinatesID	= 0;
};

struct Mesh_Node
{
	std::string								m_name;
	std::vector<std::shared_ptr<Mesh_Node>>	m_nodes;
	std::vector<std::shared_ptr<Mesh_Data>> m_attachedMeshes;
	glm::mat4x4								m_localTransform;
};


class Mesh : public IRender
{
	friend class Loader3D;
	friend class MeshBuilder;
protected:
	
	std::vector<std::shared_ptr<Mesh_Data>>	m_meshData;
	std::shared_ptr<Mesh_Node>				m_rootNode;

public:

	Mesh() {};
	virtual ~Mesh() = 0 {};

	virtual std::shared_ptr<Mesh> DynamicInstance() const = 0;
	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override = 0;

	std::vector<std::shared_ptr<Mesh_Data>> GetMeshData()
	{
		return m_meshData;
	}
	std::shared_ptr<Mesh_Node> GetRootNode()
	{
		return m_rootNode;
	}

protected:
	virtual void initialise() const = 0;
};