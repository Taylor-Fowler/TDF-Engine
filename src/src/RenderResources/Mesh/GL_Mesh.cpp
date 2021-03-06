#include <iostream>

#include "GL\glew.h"

#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "GL_Mesh.h"
#include "..\Program\Program.h"

GL_Mesh::~GL_Mesh()
{
	for (std::shared_ptr<Mesh_Data> meshData : m_meshData)
	{
		glDeleteBuffers(1, &meshData->m_verticesID);
		glDeleteBuffers(1, &meshData->m_normalsID);
		glDeleteBuffers(1, &meshData->m_textureCoordinatesID);
		glDeleteBuffers(1, &meshData->m_indicesID);
		glDeleteVertexArrays(1, &meshData->m_vaoID);
	}
}

void GL_Mesh::Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails)
{
	glm::mat4 identity(renderDetails.transformMatrix);
	renderNode(m_rootNode, identity, program, renderDetails.viewMatrix);
}

void GL_Mesh::renderNode(std::shared_ptr<Mesh_Node> node, glm::mat4 & transformations, std::shared_ptr<Program>& program, const glm::mat4& viewMatrix) const
{
	glm::mat4 transform = transformations * node->m_localTransform;
	glm::mat4 modelViewMatrix = viewMatrix * transform;
	program->SendParam((std::string)"modelMatrix", glm::value_ptr(transform));
	program->SendParam((std::string)"modelViewMatrix", glm::value_ptr(modelViewMatrix));

	

	for (std::shared_ptr<Mesh_Data> meshData : node->m_attachedMeshes)
	{
		glBindVertexArray(meshData->m_vaoID);
		glDrawElements(GL_TRIANGLES, meshData->m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	for(std::shared_ptr<Mesh_Node> nextNode : node->m_nodes)
		renderNode(nextNode, transform, program, viewMatrix);
}

void GL_Mesh::initialise() const
{
	for (std::shared_ptr<Mesh_Data> meshData : m_meshData)
	{
		glGenVertexArrays(1, &meshData->m_vaoID);
		glBindVertexArray(meshData->m_vaoID);


		auto vSize = sizeof(meshData->m_vertices[0]) * meshData->m_vertices.size();
		glGenBuffers(1, &meshData->m_verticesID);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->m_verticesID);
		glBufferData(GL_ARRAY_BUFFER, vSize, &meshData->m_vertices[0], GL_STATIC_DRAW);

		// Vertices bind point = 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		auto nSize = sizeof(meshData->m_normals[0]) * meshData->m_normals.size();
		glGenBuffers(1, &meshData->m_normalsID);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->m_normalsID);
		glBufferData(GL_ARRAY_BUFFER, nSize, &meshData->m_normals[0], GL_STATIC_DRAW);
		// Normals bind point = 1
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		auto tSize = sizeof(meshData->m_textureCoordinates[0]) * meshData->m_textureCoordinates.size();
		glGenBuffers(1, &meshData->m_textureCoordinatesID);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->m_textureCoordinatesID);
		glBufferData(GL_ARRAY_BUFFER, tSize, &meshData->m_textureCoordinates[0], GL_STATIC_DRAW);
		// Texture Coordinates bind point = 2
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		auto iSize = sizeof(meshData->m_indices[0]) * meshData->m_indices.size();
		glGenBuffers(1, &meshData->m_indicesID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->m_indicesID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, &meshData->m_indices[0], GL_STATIC_DRAW);


		// Reset
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
