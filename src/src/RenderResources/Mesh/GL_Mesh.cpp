#include "GL\glew.h"

#include "glm\gtc\type_ptr.hpp"

#include "GL_Mesh.h"
#include "..\Program\Program.h"

void GL_Mesh::Render(std::shared_ptr<Program>& program) const
{
	glm::mat4x4 identity;
	renderNode(m_rootNode, identity, program);
}

void GL_Mesh::renderNode(std::shared_ptr<Mesh_Node> node, glm::mat4x4 & transformations, std::shared_ptr<Program>& program) const
{
	glm::mat4x4 transform = transformations * node->m_localTransform;
	program->SendParam((std::string)"modelMatrix", glm::value_ptr(transform));

	for (std::shared_ptr<Mesh_Data> meshData : node->m_attachedMeshes)
	{
		glBindVertexArray(meshData->m_vaoID);
		glDrawElements(GL_TRIANGLES, meshData->m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	for(std::shared_ptr<Mesh_Node> nextNode : node->m_nodes)
		renderNode(nextNode, transform, program);
}

void GL_Mesh::initialise() const
{
	for (std::shared_ptr<Mesh_Data> meshData : m_meshData)
	{
		glGenVertexArrays(1, &meshData->m_vaoID);
		glBindVertexArray(meshData->m_vaoID);

		glGenBuffers(1, &meshData->m_verticesID);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->m_verticesID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(meshData->m_vertices), &meshData->m_vertices[0], GL_STATIC_DRAW);
		// Vertices bind point = 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &meshData->m_normalsID);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->m_normalsID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(meshData->m_normals), &meshData->m_normals[0], GL_STATIC_DRAW);
		// Normals bind point = 0
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &meshData->m_textureCoordinatesID);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->m_textureCoordinatesID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(meshData->m_textureCoordinates), &meshData->m_textureCoordinates[0], GL_STATIC_DRAW);
		// Texture Coordinates bind point = 0
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &meshData->m_indicesID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->m_indicesID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(meshData->m_indices), &meshData->m_indices[0], GL_STATIC_DRAW);


		// Reset
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
