#pragma once

#include "Mesh.h"

// Forward declarations.
namespace physx
{
	class PxTriangleMesh;
}

using namespace physx;

struct BoundingBox {
	glm::vec3 size;
	glm::vec3 offsetFromModelOrigin;
};

class Model
{
public:
	void Load(std::string filepath);
	void Draw();
	void CreateTriangleMesh();
	//void Draw(Shader* shader, glm::mat4 modelMatrix, int primitiveType = GL_TRIANGLES);
	
public:
	std::vector<Mesh> _meshes; 
	std::vector<Triangle> _triangles;;
	//std::vector<int> _meshIndices;
	std::vector<std::string> _meshNames;
	PxTriangleMesh* _triangleMesh = nullptr;

public:
	std::string _name;
	std::string _filename;
	BoundingBox _boundingBox;
};
