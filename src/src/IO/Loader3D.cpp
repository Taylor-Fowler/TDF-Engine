#include <iostream>

#include "Loader3D.h"

glm::mat4x4 Loader3D::AssimpToGlm(const aiMatrix4x4 & from)
{
	return glm::mat4x4(
		from.a1, from.b1, from.c1, from.d1,
		from.a2, from.b2, from.c2, from.d2,
		from.a3, from.b3, from.c3, from.d3,
		from.a4, from.b4, from.c4, from.d4
	);
}

std::shared_ptr<GL_Mesh> Loader3D::LoadGL_3D_Model(const std::string & file)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(file.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (pScene == nullptr)
	{
		std::cout << "Warning: Loading 3D object from file failed, imported could not read file structure. File:" << file << std::endl;
		return std::shared_ptr<GL_Mesh>();
	}

	if (pScene->HasMeshes())
	{
		return initialiseFromSceneGL(pScene);
	}

	return std::shared_ptr<GL_Mesh>();
}

std::shared_ptr<GL_Mesh> Loader3D::initialiseFromSceneGL(const aiScene * pScene)
{
	if (pScene->mNumMeshes == 0)
	{
		std::cout << "Warning: 0 meshes found while loading a 3D object from file." << std::endl;
		return std::shared_ptr<GL_Mesh>();
	}

	if (pScene->mRootNode == NULL)
	{
		std::cout << "Warning: 3D object root node is NULL when loading from file." << std::endl;
		return std::shared_ptr<GL_Mesh>();
	}

	std::shared_ptr<GL_Mesh> mesh = std::make_shared<GL_Mesh>();
	mesh->m_meshData.resize(pScene->mNumMeshes);

	// Load the mesh data into the mesh class
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
	{
		std::shared_ptr<Mesh_Data> meshData = std::make_shared<Mesh_Data>();
		mesh->m_meshData[i] = meshData;

		aiMesh* assimpMesh = pScene->mMeshes[i];

		setName(assimpMesh, meshData);

		if (assimpMesh->mNumVertices > 0)
			setVertices(assimpMesh, meshData);

		if (assimpMesh->HasNormals())
			setNormals(assimpMesh, meshData);

		if (assimpMesh->HasTextureCoords(0))
			SetTextureCoordinates(assimpMesh, meshData.get());

		setIndices(assimpMesh, meshData);
	}

	mesh->m_rootNode = std::make_shared<Mesh_Node>();

	recursiveProcessNode(pScene->mRootNode, mesh->m_rootNode, mesh->m_meshData);
	mesh->initialise();

	return mesh;
}

void Loader3D::setName(const aiMesh * assimpMesh, std::shared_ptr<Mesh_Data>& mesh)
{
	mesh->m_name = assimpMesh->mName.length == 0 ? "" : assimpMesh->mName.C_Str();
}

void Loader3D::setVertices(const aiMesh * assimpMesh, std::shared_ptr<Mesh_Data>& mesh)
{
	for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
	{
		aiVector3D &vec = assimpMesh->mVertices[i];

		mesh->m_vertices.push_back(vec.x);
		mesh->m_vertices.push_back(vec.y);
		mesh->m_vertices.push_back(vec.z);
	}
}

void Loader3D::setNormals(const aiMesh * assimpMesh, std::shared_ptr<Mesh_Data>& mesh)
{
	for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
	{
		aiVector3D &vec = assimpMesh->mNormals[i];

		mesh->m_normals.push_back(vec.x);
		mesh->m_normals.push_back(vec.y);
		mesh->m_normals.push_back(vec.z);
	}
}

void Loader3D::setIndices(const aiMesh * assimpMesh, std::shared_ptr<Mesh_Data>& mesh)
{
	for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i)
	{
		aiFace* face = &assimpMesh->mFaces[i];
		if (face->mNumIndices != 3)
		{
			std::cout << "Warning: Loading Mesh " << mesh->m_name << ", face " << i << " does not have 3 indices, ignoring face." << std::endl;
			continue;
		}

		mesh->m_indices.push_back(face->mIndices[0]);
		mesh->m_indices.push_back(face->mIndices[1]);
		mesh->m_indices.push_back(face->mIndices[2]);
	}
}

void Loader3D::SetTextureCoordinates(const aiMesh * assimpMesh, Mesh_Data * const mesh)
{
	mesh->m_textureCoordinates.resize(assimpMesh->mNumVertices * 2);
	for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
	{
		mesh->m_textureCoordinates[i * 2] = assimpMesh->mTextureCoords[0][i].x;
		mesh->m_textureCoordinates[i * 2 + 1] = assimpMesh->mTextureCoords[0][i].y;
	}
}

void Loader3D::recursiveProcessNode(aiNode * process, std::shared_ptr<Mesh_Node>& meshNode, std::vector<std::shared_ptr<Mesh_Data>> &meshData)
{
	meshNode->m_name = process->mName.length == 0 ? "" : process->mName.C_Str();
	meshNode->m_localTransform = AssimpToGlm(process->mTransformation);

	meshNode->m_attachedMeshes.resize(process->mNumMeshes);

	for (unsigned int i = 0; i < process->mNumMeshes; ++i)
	{
		meshNode->m_attachedMeshes[i] = meshData[process->mMeshes[i]];
	}

	meshNode->m_nodes.resize(process->mNumChildren);

	for (unsigned int i = 0; i < process->mNumChildren; ++i)
	{
		meshNode->m_nodes[i] = std::make_shared<Mesh_Node>();
		recursiveProcessNode(process->mChildren[i], meshNode->m_nodes[i], meshData);
	}
}
