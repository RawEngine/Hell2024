#pragma once

// Forward declarations.
namespace physx
{
	class PxTriangleMesh;
	class PxConvexMesh;
}

using namespace physx;

class Mesh {

	public:
		Mesh();
		Mesh (std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string name);
		void Draw();
		int GetIndexCount();
		int GetVAO();
		void CreateTriangleMesh();
		void CreateConvexMesh();

	public:
		unsigned int _VBO = 0;
		unsigned int _VAO = 0;
		unsigned int _EBO = 0;
		unsigned int _indexCount = 0;
		std::string _name;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		PxTriangleMesh* _triangleMesh = nullptr;
		PxConvexMesh* _convexMesh = nullptr;
};