
#include <iostream>
#include "Core/Parser.h"
#include "Core/Ray.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include "GeometricEntities/Sphere.h"
#include "GeometricEntities/Plane.h"

using namespace std;

struct vector2
{
	float x;
	float y;
};

struct vector4
{
	float x;
	float y;
	float z;
	float w;
};


int main()
{
	string output = Parser::Parse("res/input1.txt");
	
	int arr[3];

	for (int asd : arr)
	{
		asd = asd;
	};

	for(int dsa : arr)
	{
		std::cout << dsa << std::endl;
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

	delete(sphere);
	delete(plane);

	return 0;
};