#pragma once
#include <vector>
#include <memory>

#include "../../assimp/Importer.hpp"
#include "../../assimp/scene.h"
#include "../../assimp/postprocess.h"

#include "../RenderResources/Mesh/Mesh.h"
#include "../RenderResources/Mesh/GL_Mesh.h"


class Loader3D
{

public:
	static glm::mat4x4 AssimpToGlm(const aiMatrix4x4 &from);
	
	std::shared_ptr<GL_Mesh> LoadGL_3D_Model(const std::string &file);

private:
	std::shared_ptr<GL_Mesh> initialiseFromSceneGL(const aiScene *pScene);


	void setName(const aiMesh *assimpMesh, std::shared_ptr<Mesh_Data> &mesh);
	void setVertices(const aiMesh *assimpMesh, std::shared_ptr<Mesh_Data> &mesh);
	void setNormals(const aiMesh *assimpMesh, std::shared_ptr<Mesh_Data> &mesh);
	void setIndices(const aiMesh *assimpMesh, std::shared_ptr<Mesh_Data> &mesh);

	void recursiveProcessNode(aiNode *process, std::shared_ptr<Mesh_Node> &meshNode, std::vector<std::shared_ptr<Mesh_Data>> &meshData);

	
};