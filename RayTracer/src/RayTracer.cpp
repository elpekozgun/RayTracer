
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

template <typename From, typename To>
struct dynamic_caster
{
	To* operator()(From* p)
	{
		return dynamic_cast<To*>(p);
	}
};


int main()
{
	vector<vector<string>>output = Parser::Parse("res/input3.txt");
	
	vector<IEntity*> Entities;
	vector<IGeometricEntity*> GeometricEntities;

	// Entities
	BackgroundColor backgroundColor;
	AmbientLight ambientLight;
	MaxRecursionDepth maxRecursionDepth;
	ShadowRayEpsilon shadowRayEpsilon;
	VertexList vertexList;
	Camera camera;
	
	for( auto& list : output )
	{
		auto entity = Parser::GenerateEntity(list);
		if( entity )
		{
			Entities.push_back(entity);
			if( entity->GetType() == eEntityType::vertexlist )
			{
				vertexList = *static_cast<VertexList*>(entity);
			}
		}
	}

	//similar to c# linq.where(x = > x.eEntityType == pointlight)
	vector<IEntity*> pointLights;
	std::copy_if
	(
		Entities.begin(), 
		Entities.end(), 
		std::back_inserter(pointLights),
		[] (IEntity* x)-> bool { return x->GetType() == eEntityType::pointlight; } // Lambda function C++11. 
	);
	
	//Camera;
	camera = *dynamic_cast<Camera*>(*std::find_if
	(
		Entities.begin(),
		Entities.end(),
		[](IEntity* x)->bool {return x->GetType() == eEntityType::camera; }
	)._Ptr);


	// Materials
	vector<IEntity*> materials;
	std::copy_if
	(
		Entities.begin(),
		Entities.end(),
		std::back_inserter(materials),
		[](IEntity* x)-> bool { return x->GetType() == eEntityType::material; } // Lambda function C++11. 
	);
	

	// Primitives
	for(auto& entity : Entities)
	{
		if(entity->GetType() == eEntityType::backgroundColor)
		{
			backgroundColor = *(dynamic_cast<BackgroundColor*>(entity));
		}
		else if(entity->GetType() == eEntityType::ambientLight)
		{
			ambientLight = *(dynamic_cast<AmbientLight*>(entity));
		}
		else if(entity->GetType() == eEntityType::maxRecursionDepth)
		{
			maxRecursionDepth = *(dynamic_cast<MaxRecursionDepth*>(entity));
		}
		else if(entity->GetType() == eEntityType::shadowRayEpsilon)
		{
			shadowRayEpsilon = *(dynamic_cast<ShadowRayEpsilon*>(entity));
		}
	}
	



	

	for(auto& list : output)
	{
		auto entity = Parser::GenerateGeometricEntity(list, vertexList);
		if(entity)
		{
			GeometricEntities.push_back(entity);
		}
	}


	

	
	
	Ray ray(Vector3(0, 0, 0), Vector3(0, 1, 0));
	for( auto& entity : GeometricEntities )
	{
		auto t = entity->Intersect(ray);
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