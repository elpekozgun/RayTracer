#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

#include "Core/Parser.h"
#include "Core/Ray.h"
#include "Core/Shader.h"
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
	auto start = chrono::high_resolution_clock::now();

	
	vector<IEntity*> Entities;
	vector<IGeometricEntity*> GeometricEntities;
	vector<vector<string>>output = Parser::Parse("res/input2.txt");
	

	// Parse Input Text
	for(unsigned int i = 0; i < output.size(); i++)
	{
		auto list = output.at(i);
		auto entity = Parser::GenerateEntity(list);
		if(entity)
		{
			Entities.push_back(entity);
			output.erase(find(output.begin(), output.end(), list));
			i--;
		}
	}

	
	//------------------------------------ENTITIES----------------------------------
	Vector3 backgroundColor;
	Vector3 ambientLight;
	int maxRecursionDepth = 0;
	float shadowRayEpsilon = 0.0f;
	vector<PointLight> pointLights;
	vector<Material> materials;
	VertexList vertexList;
	Camera camera;
	vector<vector<Vector3>> Image;
	

	// Entities
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
		else if(entity->GetType() == eEntityType::material)
		{
			materials.push_back(*dynamic_cast<Material*>(entity));
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::pointlight)
		{
			pointLights.push_back(*dynamic_cast<PointLight*>(entity));
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::vertexlist)
		{
			vertexList = *dynamic_cast<VertexList*>(entity);
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::camera)
		{
			camera = *dynamic_cast<Camera*>(entity);
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else
		{
			i++;
		}
	}

	//C++ 11 lambda expression, query similar to C# linq.Where(x = > x.GetType() == eEntityType.camera)
	//camera = *dynamic_cast<Camera*>(*std::find_if
	//(
	//								Entities.begin(),
	//								Entities.end(),
	//								[](IEntity* x)->bool { return x->GetType() == eEntityType::camera; } 
	//)._Ptr);
	Image.resize((int)camera.ScreenResolution.x, std::vector<Vector3>((int)camera.ScreenResolution.y));

	
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

	float tMin = INFINITY;
	float t = 0;
	IGeometricEntity* closestObject = nullptr;

	for(unsigned int j = 0; j < camera.ScreenResolution.y; j++)
	{
		for(unsigned int i = 0; i < camera.ScreenResolution.x; i++)
		{
			tMin = INFINITY;

			Ray ray(camera.Position, camera.GetScreenPixel(i,j));
			for(auto& entity : GeometricEntities)
			{
				// Costly?? Maybe predefined?
				int matId = entity->MaterialID();
				Material mat = *std::find_if(materials.begin(), materials.end(), [matId](Material& y) -> bool { return y.ID == matId; })._Ptr;

				if(((Mesh*)entity)->GetType() == eEntityType::mesh)
				{
					auto mesh = dynamic_cast<Mesh*>(entity);
					for(auto& triangle : mesh->Triangles)
					{
						t = triangle.Intersect(ray);
						Vector3 hitpoint = ray.origin + ray.direction * t;
						if(t > 0 && t <= tMin)
						{
							closestObject = &triangle;
							tMin = t;
							Image.at(j).at(i) = Shader::CalculateLighting(GeometricEntities, hitpoint, triangle.GetNormal(hitpoint), camera.Position, mat, pointLights,ambientLight, shadowRayEpsilon);
						}
					}
				}
				else
				{
					t = entity->Intersect(ray);
					Vector3 hitpoint = ray.origin + ray.direction * t;
					if(t > 0 && t <= tMin)
					{
						tMin = t;
						closestObject = entity;
						Image.at(j).at(i) = Shader::CalculateLighting(GeometricEntities, hitpoint, entity->GetNormal(hitpoint), camera.Position, mat, pointLights, ambientLight, shadowRayEpsilon);
					}
				}
			}

		}
	}
	auto finish = chrono::high_resolution_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start) / 1e6;
	std::cout << "time elapsed: " << seconds.count() << "seconds" << endl; 


	
	Parser::GeneratePPMfile((int)camera.ScreenResolution.x, (int)camera.ScreenResolution.y, Image);


	for (IEntity* entity : Entities)
	{
		delete entity;
	}
	for( IGeometricEntity* entity : GeometricEntities )
	{
		delete entity;
	}
	delete closestObject;
	
	return 0;
};