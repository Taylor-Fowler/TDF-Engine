#pragma once
#include "Mesh.h"


class GL_Mesh : public Mesh
{
public:

	~GL_Mesh() override {};


	void Render(std::shared_ptr<Program>& program) const override;

	std::shared_ptr<Mesh> DynamicInstance() const override {
		return std::shared_ptr<Mesh>();
	};

protected:
	void renderNode(std::shared_ptr<Mesh_Node> node, glm::mat4x4 &transformations, std::shared_ptr<Program>& program) const;
	void initialise() const override;
};