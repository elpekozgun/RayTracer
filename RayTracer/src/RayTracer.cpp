
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

using namespace std;


int main()
{
	Parser parser;

	std::vector<std::vector<std::string>>output = Parser::Parse("res/input3.txt");
	
	std::vector<IEntity*> listOfEntities;

	for (int i = 0; i < output.size(); i++)
	{
		IEntity* entity = Parser::GenerateObject(output[i]);
		listOfEntities.push_back(entity);
	}












	// Test inherited call.
	std::vector<IGeometricEntity*> entities;
	std::vector<float> intersectionTimes;

	Ray ray(Vector3(0, 0, 0), Vector3(0, 1, 0));
	Sphere* sphere = new Sphere(Vector3(0, 5, 0), 3);
	Plane* plane = new Plane(Vector3(0 , 0.5, 0.5));

	entities.push_back(sphere);
	entities.push_back(plane);

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		intersectionTimes.push_back(entities[i]->Intersect(ray));
	}

	for (IEntity* entity : listOfEntities)
	{
		delete entity;
	}
	
	delete(sphere);
	delete(plane);

	return 0;
};