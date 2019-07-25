#include "KdNode.h"


KdNode::KdNode(std::vector<Triangle*>& triangles, ePartitionAxis currentAxis)
{
	SortPoints(triangles, currentAxis);

	this->Triangles = triangles;
	size_t half = triangles.size() >> 1;

	if(triangles.size() > 2)
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
	
	
		this->Boundingbox = CalculateBoundingBox(triangles);
		this->Left = new KdNode(leftTris, NextAxis(currentAxis));
		this->Right = new KdNode(rightTris, NextAxis(currentAxis));
	}
	else
	{
		this->Right = NULL;
		this->Left = NULL;
	}

}

KdNode::~KdNode()
{
	delete Left;
	delete Right;
	
}

Box KdNode::CalculateBoundingBox(std::vector<Triangle*> triangles)
{
	SortPoints(triangles, ePartitionAxis::X);

	auto triFront = triangles.front();
	auto triBack = triangles.back();

	auto xMin = triFront->Vertices[0].X;
	if(triFront->Vertices[1].X < xMin)
	{
		xMin = triFront->Vertices[1].X;
	}
	if(triFront->Vertices[2].X < xMin)
	{
		xMin = triFront->Vertices[2].X;
	}

	auto xMax = triBack->Vertices[0].X;
	if(triBack->Vertices[1].X > xMax)
	{
		xMax = triBack->Vertices[1].X;
	}
	if(triBack->Vertices[2].X > xMax)
	{
		xMax = triBack->Vertices[2].X;
	}

	SortPoints(triangles, ePartitionAxis::Y);
	triFront = triangles.front();
	triBack = triangles.back();

	auto yMin = triFront->Vertices[0].Y;
	if(triFront->Vertices[1].Y < yMin)
	{
		yMin = triFront->Vertices[1].Y;
	}
	if(triFront->Vertices[2].Y < yMin)
	{
		yMin = triFront->Vertices[2].Y;
	}

	auto yMax = triBack->Vertices[0].Y;
	if(triBack->Vertices[1].Y > yMax)
	{
		yMax = triBack->Vertices[1].Y;
	}
	if(triBack->Vertices[2].Y > yMax)
	{
		yMax = triBack->Vertices[2].Y;
	}

	SortPoints(triangles, ePartitionAxis::Z);
	triFront = triangles.front();
	triBack = triangles.back();

	auto zMin = triFront->Vertices[0].Z;
	if(triFront->Vertices[1].Z < zMin)
	{
		zMin = triFront->Vertices[1].Z;
	}
	if(triFront->Vertices[2].Z < zMin)
	{
		zMin = triFront->Vertices[2].Z;
	}

	auto zMax = triBack->Vertices[0].Z;
	if(triBack->Vertices[1].Z > zMax)
	{
		zMax = triBack->Vertices[1].Z;
	}
	if(triBack->Vertices[2].Z > zMax)
	{
		zMax = triBack->Vertices[2].Z;
	}

	return Box(Vector3(xMin - 0.002f,yMin - 0.002f,zMin - 0.002f ), Vector3(xMax + 0.002f,yMax + 0.002f,zMax + 0.002f));
}

//Sphere KdNode::CalculateBoundingBox(std::vector<Triangle*> triangles)
//{
//	Vector3 center;
//	for(unsigned int i = 0; i < triangles.size(); i++)
//	{
//		center += triangles.at(i)->GetCenter();
//	}
//	center /= triangles.size();
//
//	float radius = 0.0f;
//	for(unsigned int i = 0; i < triangles.size(); i++)
//	{
//		float r = Triangles.at(i)->GetCenter().DistanceTo(center);
//		if(r > radius)
//		{
//			radius = r;
//		}
//	}
//
//	return Sphere(-1, -1, center, radius);
//}

void KdNode::SortPoints(std::vector<Triangle*>& triangles, ePartitionAxis axis)
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
			std::sort(triangles.begin(), triangles.end(), [](Triangle* A, Triangle* B) { return A->GetCenter().X <= B->GetCenter().X; });
			break;
	}
	
}

ePartitionAxis KdNode::NextAxis(ePartitionAxis axis)
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
	Triangle* tri = NULL;
	float tMin = INFINITY;

	if(this->Boundingbox.Intersect(ray).first > 0)
	{

		auto leftOutput = this->Left->Intersect(ray);
		auto rightOutput = this->Right->Intersect(ray);
		
		if(leftOutput.first > 0 && rightOutput.first > 0)
		{
			if(leftOutput.first < rightOutput.first)
			{
				return leftOutput;
			}
			else
			{
				return rightOutput;
			}
		} 
		else if(leftOutput.first > 0)
		{
			return leftOutput;
		}
		else if(rightOutput.first > 0)
		{
			return rightOutput;
		}
	}

	if(this->Left == NULL && this->Right == NULL)
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
		if(tMin == INFINITY)
		{
			tMin = 0;
		}
		return std::pair<float, IGeometricEntity*>(tMin, tri);
	}

	return std::pair<float, IGeometricEntity*>(0, NULL);
}

Vector3 KdNode::GetNormal(Vector3 point)
{
	return Vector3();
}

eEntityType KdNode::GetType()
{
	return eEntityType::mesh;
}

int KdNode::ID()
{
	return 0;
}

int KdNode::MaterialID()
{
	return materialId;
}



