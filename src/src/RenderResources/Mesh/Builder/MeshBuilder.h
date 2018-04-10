#pragma once
#include "..\GL_Mesh.h"

// Should be OpenGL specific but no time...
class MeshBuilder
{
private:
	std::shared_ptr<GL_Mesh> m_createdMesh;
	std::shared_ptr<Mesh_Data> m_currentData;
	std::shared_ptr<Mesh_Node> m_currentNode;

public:
	MeshBuilder()
	{
		m_createdMesh = std::make_shared<GL_Mesh>();
	};

	void CreateMeshData(const std::string& name)
	{
		m_currentData = std::make_shared<Mesh_Data>();
		m_currentData->m_name = name;
	};
	void CreateMeshNode(const std::string& name)
	{
		m_currentNode = std::make_shared<Mesh_Node>();
		m_currentNode->m_name = name;
	};

	void SetVertices(const std::vector<float>& vertices)
	{
		if (m_currentData != nullptr)
			m_currentData->m_vertices = vertices;
	};
	void SetNormals(const std::vector<float>& normals)
	{
		if (m_currentData != nullptr)
			m_currentData->m_normals = normals;
	};
	void SetIndices(const std::vector<unsigned int>& indices)
	{
		if (m_currentData != nullptr)
			m_currentData->m_indices = indices;
	};

	void SetTextureCoordinates(const std::vector<float>& textureCoordinates)
	{
		if (m_currentData != nullptr)
			m_currentData->m_textureCoordinates = textureCoordinates;
	};

	void AttachMeshData()
	{
		if (m_currentData != nullptr)
		{
			if (m_currentNode != nullptr)
				m_currentNode->m_attachedMeshes.push_back(m_currentData);

			m_createdMesh->m_meshData.push_back(m_currentData);
			m_currentData.reset();
		}
	};

	void SetTransform(glm::mat4 transform)
	{
		if (m_currentNode != nullptr)
			m_currentNode->m_localTransform = transform;
	};

	void AddMeshNode()
	{
		if(m_currentNode != nullptr)
			m_createdMesh->m_rootNode = m_currentNode;
		m_currentNode.reset();
	};



	std::shared_ptr<Mesh> GetMesh()
	{
		m_createdMesh->initialise();
		return m_createdMesh;
	}


};