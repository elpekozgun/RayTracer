#include "Mesh.h"

Mesh::Mesh()
{
	ID = -1;
	MaterialID = -1;
	Triangles = std::vector<Triangle>{};
}

Mesh::Mesh(int id,int materialID)
{
	ID = id;
	MaterialID = materialID;
	std::vector<Triangle> Triangles;
}

Mesh::~Mesh()
{
}

float Mesh::Intersect(Ray ray)
{
	for(auto& triangle : this->Triangles)
	{
		triangle.Intersect(ray);
	}
	return 0;
}

eEntityType Mesh::GetType()
{
	return eEntityType::mesh;
}



