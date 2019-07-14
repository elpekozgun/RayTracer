#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Core/Parser.h"
#include "Core/Ray.h"
#include "GeometricEntities/IGeometricEntity.h"
#include "GeometricEntities/Sphere.h"
#include "GeometricEntities/Plane.h"
#include "GeometricEntities/Mesh.h"
#include "Entities/IEntity.h"

using namespace std;

template<typename T>
inline void DeleteItemAndEraseFromVector(vector<T*>& Entities, T* entity)
{
	std::vector<T*>::iterator itr = std::find(Entities.begin(), Entities.end(), entity);
	delete(entity);
	Entities.erase(itr);
}

template<typename T>
inline void EraseFromVector(vector<T*>& Entities, T* entity)
{
	std::vector<T*>::iterator itr = std::find(Entities.begin(), Entities.end(), entity);
	Entities.erase(itr);
}


int main()
{
	vector<vector<string>>output = Parser::Parse("res/input1.txt");
	
	vector<IEntity*> Entities;
	vector<IGeometricEntity*> GeometricEntities;
	
	

	//------------------------------------ENTITIES----------------------------------
	Vector3 backgroundColor;
	Vector3 ambientLight;
	int maxRecursionDepth;
	float shadowRayEpsilon;

	VertexList vertexList;
	Camera camera;

	vector<vector<Vector3>> Image;
	
	// Parse Input Text
	for(unsigned int i = 0; i < output.size(); i++)
	{
		auto list = output.at(i);
		auto entity = Parser::GenerateEntity(list);
		if( entity )
		{
			Entities.push_back(entity);
			if( entity->GetType() == eEntityType::vertexlist )
			{
				vertexList = *static_cast<VertexList*>(entity);
			}
			output.erase(find(output.begin(),output.end(),list));
			i--;
		}
	}

	// Camera
	camera = *dynamic_cast<Camera*>(*std::find_if
	(
		Entities.begin(),
		Entities.end(),
		[](IEntity* x)->bool { return x->GetType() == eEntityType::camera; }
	)._Ptr);
	Image.resize((int)camera.ScreenResolution.x, std::vector<Vector3>((int)camera.ScreenResolution.y));

	// Primitives

	for(unsigned int i = 0; i < Entities.size(); i)
	{
		auto entity = Entities.at(i);
		if(entity->GetType() == eEntityType::backgroundColor)
		{
			backgroundColor = (dynamic_cast<BackgroundColor*>(entity))->BackgroundColorValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::ambientLight)
		{
			ambientLight = (dynamic_cast<AmbientLight*>(entity))->AmbientLightValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::maxRecursionDepth)
		{
			maxRecursionDepth = (dynamic_cast<MaxRecursionDepth*>(entity))->MaxRecursionDepthValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::shadowRayEpsilon)
		{
			shadowRayEpsilon = (dynamic_cast<ShadowRayEpsilon*>(entity))->ShadowRayEpsilonValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else
		{
			i++;
		}
	}

	// Pointlights
	vector<IEntity*> pointLights;
	std::copy_if
	(
		Entities.begin(), 
		Entities.end(), 
		std::back_inserter(pointLights),
		[] (IEntity* x)-> bool { return x->GetType() == eEntityType::pointlight; } // Lambda function C++11. //similar to c# linq.where(x = > x.eEntityType == pointlight)
	);
	
	// Materials
	vector<IEntity*> materials;
	std::copy_if
	(
		Entities.begin(),
		Entities.end(),
		std::back_inserter(materials),
		[](IEntity* x)-> bool { return x->GetType() == eEntityType::material; } // Lambda function C++11. 
	);
	
	
	//----------------------------------GEOMETRIC ENTITIES--------------------------------

	for(auto& list : output)
	{
		auto entity = Parser::GenerateGeometricEntity(list, vertexList);
		if(entity)
		{
			GeometricEntities.push_back(entity);
		}
	}

	// Main Algorithm.

	float minT = -478939101.0f;
	IGeometricEntity* closestObject = nullptr;

	for(unsigned int i = 0; i < camera.ScreenResolution.x; i++)
	{
		for(unsigned int j = 0; j < camera.ScreenResolution.y; j++)
		{

			Ray ray(camera.Position, camera.GetScreenPixel(i,j));
			for(auto& entity : GeometricEntities)
			{
				if(((Mesh*)entity)->GetType() == eEntityType::mesh)
				{
					auto mesh = dynamic_cast<Mesh*>(entity);
					for(auto& triangle : mesh->Triangles)
					{
						auto t = triangle.Intersect(ray);
					}
				}
				else
				{
					auto t= entity->Intersect(ray);
				}
			}

		}
	}










	for (IEntity* entity : Entities)
	{
		delete entity;
	}
	for( IGeometricEntity* entity : GeometricEntities )
	{
		delete entity;
	}
	
	return 0;
};