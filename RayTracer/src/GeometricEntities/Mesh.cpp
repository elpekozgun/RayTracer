#include "Mesh.h"


Mesh::Mesh()
{
	Id = -1;
	MaterialId = -1;
	Triangles = std::vector<Triangle*>{};
}

Mesh::Mesh(int id, int materialID, std::vector<Triangle*>& triangles, ePartitionAxis currentAxis)
{
	Id = id;
	MaterialId = materialID;

	SortPoints(triangles, currentAxis);

	this->Triangles = triangles;
	size_t half = triangles.size() >> 1;

	if(triangles.size() > 1)
	{
		std::vector<Triangle*> leftTris;
		for(size_t i = 0; i < half; i++)
		{
			leftTris.push_back(Triangles.at(i));
		}

		std::vector<Triangle*> rightTris;
		for(size_t i = half; i < triangles.size(); i++)
		{
			rightTris.push_back(Triangles.at(i));
		}


		this->Left = new Mesh(id, materialID, leftTris, NextAxis(currentAxis));
		this->Right = new Mesh(id, materialID, rightTris, NextAxis(currentAxis));
		this->Boundingbox = CalculateBoundingBox(triangles);
	}
	else
	{
		this->Right = NULL;
		this->Left = NULL;
	}

}

Mesh::~Mesh()
{
	if(Right != NULL && Left != NULL)
	{
		delete Right;	
		delete Left;
	}
	else
	{
		for(auto& tri : Triangles)
		{
			delete tri;
		}
	}
}

IGeometricEntity* Mesh::Intersect(Ray ray, float& t)
{
	Triangle* tri = NULL;
	float tMin = INFINITY;

	if (this->Left == NULL && this->Right == NULL)
	{
		for (auto& triangle : this->Triangles)
		{
			triangle->Intersect(ray, t);
			if (t > 0 && t <= tMin)
			{
				tMin = t;
				tri = triangle;
			}
		}
		if (tMin == INFINITY)
		{
			tMin =  0 ;
		}

		t = tMin;
		return tri;
	}

	float tCalc = 0.0f;
	this->Boundingbox.Intersect(ray, tCalc);
	if (this->Boundingbox.isPointInside(ray.origin) == false && tCalc > 0 ||
		this->Boundingbox.isPointInside(ray.origin) == true && this->Left != NULL && this->Right != NULL)
	{
		float tLeft = 0;
		float tRight = 0;

		auto leftOutput = this->Left->Intersect(ray, tLeft);
		if (tLeft > 0)
		{
			auto rightOutput = this->Right->Intersect(ray, tRight);
			if (tRight > 0)
			{
				if (tRight < tLeft)
				{
					t = tRight;
					return rightOutput;
				}
				else
				{
					t = tLeft;
					return leftOutput;
				}
			}
			else
			{
				t = tLeft;
				return leftOutput;
			}
		}
		else
		{
			auto rightOutput = this->Right->Intersect(ray, tRight);
			if (tRight > 0)
			{
				t = tRight;
				return rightOutput;
			}
		}

	}
	t = 0;
	return NULL;
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

Box Mesh::CalculateBoundingBox(std::vector<Triangle*> triangles)
{
	auto xMin = INFINITY;
	auto yMin = INFINITY;
	auto zMin = INFINITY;
	auto xMax = -INFINITY;
	auto yMax = -INFINITY;
	auto zMax = -INFINITY;

	for(auto& triangle : triangles)
	{
		for(size_t i = 0; i < 3; i++)
		{
			xMin = triangle->Vertices[i].X < xMin ? triangle->Vertices[i].X : xMin;
			xMax = triangle->Vertices[i].X > xMax ? triangle->Vertices[i].X : xMax;

			yMin = triangle->Vertices[i].Y < yMin ? triangle->Vertices[i].Y : yMin;
			yMax = triangle->Vertices[i].Y > yMax ? triangle->Vertices[i].Y : yMax;

			zMin = triangle->Vertices[i].Z < zMin ? triangle->Vertices[i].Z : zMin;
			zMax = triangle->Vertices[i].Z > zMax ? triangle->Vertices[i].Z : zMax;

		}
	}

	return Box(Vector3(xMin, yMin, zMin), Vector3(xMax, yMax, zMax));
}

void Mesh::SortPoints(std::vector<Triangle*>& triangles, ePartitionAxis axis)
{
	switch(axis)
	{
		case ePartitionAxis::X:
			std::sort(triangles.begin(), triangles.end(), [](Triangle* A, Triangle* B) { return A->GetCenter().X < B->GetCenter().X; });
			break;
		case ePartitionAxis::Y:
			std::sort(triangles.begin(), triangles.end(), [](Triangle* A, Triangle* B) { return A->GetCenter().Y < B->GetCenter().Y; });
			break;
		case ePartitionAxis::Z:
			std::sort(triangles.begin(), triangles.end(), [](Triangle* A, Triangle* B) { return A->GetCenter().Z < B->GetCenter().Z; });
			break;
		default:
			std::sort(triangles.begin(), triangles.end(), [](Triangle* A, Triangle* B) { return A->GetCenter().X < B->GetCenter().X; });
			break;
	}
}

ePartitionAxis Mesh::NextAxis(ePartitionAxis axis)
{
	switch(axis)
	{
		case ePartitionAxis::X:
			return ePartitionAxis::Y;
		case ePartitionAxis::Y:
			return ePartitionAxis::Z;
		case ePartitionAxis::Z:
			return ePartitionAxis::X;
		default:
			return ePartitionAxis::X;
	}
}



