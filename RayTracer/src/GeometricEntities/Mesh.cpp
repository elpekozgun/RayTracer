#include "Mesh.h"


Mesh::Mesh()
{
	Id = -1;
	MaterialId = -1;
	Triangles = std::vector<Triangle>{};
}

Mesh::Mesh(int id,int materialID)
{
	Id = id;
	MaterialId = materialID;
	std::vector<Triangle> Triangles;
}

Mesh::~Mesh()
{
	 std::cout << "mesh deleted" << std::endl;
}

float Mesh::Intersect(Ray ray)
{
	for(auto& triangle : this->Triangles)
	{
		triangle.Intersect(ray);
	}
	return 0;
}

Vector3 Mesh::GetNormal(Vector3 point)
{
	// No need normal for this object.
	return Vector3();
}

eEntityType Mesh::GetType()
{
	return eEntityType::mesh;
}

int Mesh::ID()
{
	return Id;
}

int Mesh::MaterialID()
{
	return MaterialId;
}



