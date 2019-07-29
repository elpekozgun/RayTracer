// RAY TRACER - OZGUN ELPEK

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

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	auto start = chrono::high_resolution_clock::now();

	vector<IEntity*> Entities;
	vector<IGeometricEntity*> GeometricEntities;
	
	vector<vector<Vector3>> Image;
	vector<Material> materials;
	VertexList* vertexList = NULL;	// Stack may not be enough.
	Camera camera;
	Scene scene;
	string fileName;
	vector<vector<string>>output;

	if(argc < 2)
	{
		output = Parser::Parse("res/input3.txt");
		fileName = "input3.ppm";
	}
	else
	{
		output = Parser::Parse(argv[1]);
		const char* asd = argv[1];
		string raw(argv[1]);
		fileName = raw.substr(0, raw.find(".txt")) + ".ppm";
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
			vertexList = dynamic_cast<VertexList*>(entity);
			EraseFromVector(Entities, entity);
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

	for(unsigned int i = 0; i < output.size(); i++)
	{
		auto list = output.at(i);
		auto entity = Parser::GenerateGeometricEntity(list, vertexList);
		if(entity)
		{
			GeometricEntities.push_back(entity);
			output.erase(find(output.begin(), output.end(), list));
			i--;
		}
	}

#pragma endregion

	auto renderer = Renderer(camera, scene, GeometricEntities, materials);
	renderer.Render(Image);

	auto finish = chrono::high_resolution_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start) / 1e6;
	std::cout << "time elapsed: " << seconds.count() << "seconds" << endl;

	Parser::GeneratePPMfile(fileName,(int)camera.ScreenResolution.x, (int)camera.ScreenResolution.y, Image);


#pragma region Dispose

	delete vertexList;
	for( IGeometricEntity* entity : GeometricEntities )
	{
		delete entity;
	}

	return 0;
	

#pragma endregion

};


