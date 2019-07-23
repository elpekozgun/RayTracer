#include "Mesh.h"


Mesh::Mesh()
{
	Id = -1;
	MaterialId = -1;
	Triangles = std::vector<Triangle*>{};
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

std::pair<float, IGeometricEntity*> Mesh::Intersect(Ray ray)
{
	float tMin = INFINITY;
	float t = 0;
	Triangle* tri = nullptr;

	for(auto& triangle : this->Triangles)
	{
		triangle->Intersect(ray).first > 0;
		if(t > 0 && t <= tMin)
		{
			tMin = t;
			hitObjectNormal = triangle->GetNormal(Vector3());
			tri = triangle;
		}
	}
	return std::pair<float,IGeometricEntity*>(t, tri);
}

Vector3 Mesh::GetNormal(Vector3 point)
{
	return hitObjectNormal;
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



