#include "KdNode.h"


KdNode::KdNode(std::vector<Triangle*>& triangles, ePartitionAxis currentAxis)
{
	SortPoints(triangles, currentAxis);

	this->Triangles = triangles;
	size_t half = triangles.size() >> 1;

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

	this->BoundingSphere = CalculateBoundingSphere(triangles);
	if(leftTris.size() > 8 || rightTris.size() > 8)
	{
		this->Left = new KdNode(leftTris, nextAxis(currentAxis));
		this->Right = new KdNode(rightTris, nextAxis(currentAxis));
	}
	else
	{
		this->Left = NULL;
		this->Right = NULL;
	}

}

KdNode::~KdNode()
{
}

Sphere KdNode::CalculateBoundingSphere(std::vector<Triangle*> triangles)
{
	Vector3 center;
	for(unsigned int i = 0; i < triangles.size(); i++)
	{
		center += triangles.at(i)->GetCenter();
	}
	center /= triangles.size();
	
	float radius = 0.0f;
	for(unsigned int i = 0; i < triangles.size(); i++)
	{
		float r = Triangles.at(i)->GetCenter().DistanceTo(center);
		if(r > radius)
		{
			radius = r;
		}
	}

	return Sphere(-1, -1, center, radius);
}

void KdNode::SortPoints(std::vector<Triangle*> triangles, ePartitionAxis axis)
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

ePartitionAxis KdNode::nextAxis(ePartitionAxis axis)
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

std::pair<float, IGeometricEntity*> KdNode::Intersect(Ray ray)
{
	Triangle* tri = nullptr;
	float tMin = INFINITY;
	if(this->BoundingSphere.Intersect(ray).first > 0 )
	{

		if(this->Left != nullptr || this->Right != nullptr)
		{
			this->Left->Intersect(ray);
			this->Right->Intersect(ray);
		}
		else
		{
			float t = 0;
			for(auto& triangle : this->Triangles)
			{
				t = triangle->Intersect(ray).first;
				if(t > 0 && t <= tMin)
				{
					tMin = t;
					tri = triangle;
				}
			}
			return std::pair<float, IGeometricEntity*>(tMin, tri);
		}
	}
}

Vector3 KdNode::GetNormal(Vector3 point)
{
	return Vector3();
}

int KdNode::ID()
{
	return 0;
}


int KdNode::MaterialID()
{
	return materialId;
}



