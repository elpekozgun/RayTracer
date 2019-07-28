#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

#include "Core/Parser.h"
#include "Core/Ray.h"
#include "Core/Renderer.h"
#include "GeometricEntities/Sphere.h"
#include "GeometricEntities/Plane.h"
#include "GeometricEntities/Mesh.h"
#include "Entities/IEntity.h"

//#include <stdlib.h>
//#include <crtdbg.h>
//
//#define _CRTDBG_MAP_ALLOC

using namespace std;

template<typename T>
inline void DeleteItemAndEraseFromVector(vector<T*>& Entities, T* entity)
{
	std::vector<T*>::iterator itr = std::find(Entities.begin(), Entities.end(), entity);
	delete entity;
	Entities.erase(itr);
}

template<typename T>
inline void EraseFromVector(vector<T*>& Entities, T* entity)
{
	std::vector<T*>::iterator itr = std::find(Entities.begin(), Entities.end(), entity);
	Entities.erase(itr);
}

int main(int argc, char** argv)
{
	auto start = chrono::high_resolution_clock::now();

	vector<IEntity*> Entities;
	vector<IGeometricEntity*> GeometricEntities;
	
	vector<vector<Vector3>> Image;
	vector<Material> materials;
	VertexList vertexList;
	Camera camera;
	Scene scene;
	
	vector<vector<string>>output;
	if(argc < 2)
	{
		output = Parser::Parse("res/input5.txt");
	}
	else
	{
		output = Parser::Parse(argv[1]);
	}

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

#pragma region Entities

	// Entities
	for(unsigned int i = 0; i < Entities.size(); i)
	{
		auto entity = Entities.at(i);
		if(entity->GetType() == eEntityType::backgroundColor)
		{
			scene.BackgroundColor = (dynamic_cast<BackgroundColor*>(entity))->BackgroundColorValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::ambientLight)
		{
			scene.AmbientLight = (dynamic_cast<AmbientLight*>(entity))->AmbientLightValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::maxRecursionDepth)
		{
			scene.RecursionDepth = (dynamic_cast<MaxRecursionDepth*>(entity))->MaxRecursionDepthValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::shadowRayEpsilon)
		{
			scene.ShadowRayEpsilon = (dynamic_cast<ShadowRayEpsilon*>(entity))->ShadowRayEpsilonValue;
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::pointlight)
		{
			scene.PointLights.push_back(*dynamic_cast<PointLight*>(entity));
			DeleteItemAndEraseFromVector(Entities, entity);
		}
		else if(entity->GetType() == eEntityType::material)
		{
			materials.push_back(*dynamic_cast<Material*>(entity));
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

	Image.resize((int)camera.ScreenResolution.y, std::vector<Vector3>((int)camera.ScreenResolution.x));
	
#pragma endregion

#pragma region Geometric Entities

	for(auto& list : output)
	{
		auto entity = Parser::GenerateGeometricEntity(list, vertexList);
		if(entity)
		{
			GeometricEntities.push_back(entity);
		}
	}

#pragma endregion

	auto renderer = Renderer(camera, scene, GeometricEntities, materials);
	renderer.Render(Image);

	auto finish = chrono::high_resolution_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start) / 1e6;
	std::cout << "time elapsed: " << seconds.count() << "seconds" << endl;

	Parser::GeneratePPMfile((int)camera.ScreenResolution.x, (int)camera.ScreenResolution.y, Image);

#pragma region Dispose


	for (IEntity* entity : Entities)
	{
		delete entity;
	}
	for( IGeometricEntity* entity : GeometricEntities )
	{
		delete entity;
	}

	return 0;
	
	//_CrtDumpMemoryLeaks();

#pragma endregion

};


