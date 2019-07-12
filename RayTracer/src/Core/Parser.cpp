#include "Parser.h"
#include <iterator>
#include <iostream>

Parser::Parser()
{
}

Parser::~Parser()
{
}

IEntity* Parser::GenerateEntity(std::vector<std::string> list)
{
	std::string heading = list[0];

	if( heading == BACKGROUNDCOLOR )
	{
		BackgroundColor* backGroundColor = new BackgroundColor();
		backGroundColor->BackgroundColorValue = ToVector3(list[1]);
		return backGroundColor;
	}
	else if( heading == MAXRECURSIONDEPTH )
	{
		MaxRecursionDepth* maxRecursionDepth = new MaxRecursionDepth();
		maxRecursionDepth->MaxRecursionDepthValue = ToInt(list[1]);
		return maxRecursionDepth;
	}
	else if( heading == SHADOWRAYEPSILON )
	{
		ShadowRayEpsilon* shadowRayepsilon = new ShadowRayEpsilon();
		shadowRayepsilon->ShadowRayEpsilonValue = SciToFloat(list[1]);
		return shadowRayepsilon;
	}
	else if( heading == AMBIENTLIGHT )
	{
		AmbientLight* ambientLight = new AmbientLight();
		ambientLight->AmbientLightValue = ToVector3(list[1]);
		return ambientLight;
	}
	else if (heading == CAMERA)
	{
		Camera* camera = new Camera();
		camera->Position = ToVector3(list[1]);
		camera->Gaze = ToVector3(list[2]);
		camera->Up = ToVector3(list[3]);
		camera->NearPlane = ToVector4(list[4]);
		camera->NearDistance = ToFloat(list[5]);
		camera->ScreenResolution = ToVector2(list[6]);

		return camera;
	}
	else if (heading == MATERIAL)
	{
		Material* material = new Material();
		material->ID = ToInt(list[1]);
		material->Ambient = ToVector3(list[2]);
		material->Diffuse = ToVector3(list[3]);
		material->Specular = ToVector3(list[4]);
		material->PhongExponent = ToFloat(list[5]);
		material->Specular = ToVector3(list[6]);

		return material;
	}
	else if (heading == POINTLIGHT)
	{
		PointLight* pointlight = new PointLight();
		pointlight->ID = ToInt(list[1]);
		pointlight->Position = ToVector3(list[2]);
		pointlight->Intensity = ToVector3(list[3]);

		return pointlight;
	}
	else if (heading == VERTEXLIST)
	{
		VertexList* vertexList = new VertexList();
		for (unsigned int i = 1; i < list.size(); i++)
		{
			// vertex index starting from 1.
			std::pair<int,Vector3> pair(i, ToVector3(list[i]));
			vertexList->vertexList.insert(pair);
		}
		return vertexList;
	}


	return nullptr;
}

IGeometricEntity* Parser::GenerateGeometricEntity(std::vector<std::string> list, VertexList vertexList)
{
	std::string heading = list[0];

	if( heading == TRIANGLE )
	{
		Triangle* triangle = new Triangle();
		triangle->ID = ToInt(list[1]);
		triangle->MaterialID = ToInt(list[2]);
		Vector3 vertices  = ToVector3(list[3]);
		triangle->Vertices[0] = vertexList.vertexList.at((int)vertices.X);
		triangle->Vertices[1] = vertexList.vertexList.at((int)vertices.Y);
		triangle->Vertices[2] = vertexList.vertexList.at((int)vertices.Z);

		return triangle;
	}
	else if( heading == SPHERE )
	{
		Sphere* sphere = new Sphere();
		sphere->ID = ToInt(list[1]);
		sphere->MaterialID = ToInt(list[2]);
		sphere->Center = vertexList.vertexList.at(ToInt(list[3]));
		sphere->Radius = ToFloat(list[4]);

		return sphere;
	}
	else if( heading == MESH )
	{
		Mesh* mesh = new Mesh();
		mesh->ID = ToInt(list[1]);
		mesh->MaterialID = ToInt(list[2]);
		for( unsigned int i = 3; i < list.size(); i++ )
		{
			Triangle triangle;
			Vector3 vertices = ToVector3(list[i]);
			triangle.Vertices[0] = vertexList.vertexList.at((int)vertices.X);
			triangle.Vertices[1] = vertexList.vertexList.at((int)vertices.Y);
			triangle.Vertices[2] = vertexList.vertexList.at((int)vertices.Z);
			mesh->Triangles.push_back(triangle);

		}

		return mesh;

	}

	return nullptr;
}

std::vector<std::vector<std::string>> Parser::Parse(std::string path)
{
	std::vector<std::vector<std::string>> returnList;

	std::fstream inputStream(path);
	std::string line;


	while (std::getline(inputStream, line))
	{
		std::vector<std::string> list;

		if (line[0] == '#')
		{
			do
			{
				list.push_back(line);
				std::getline(inputStream, line);
			} while (!line.empty());
			returnList.push_back(list);
		}
	}
	

	return returnList;
}

Vector4 Parser::ToVector4(std::string line)
{
	std::istringstream iss(line);
	std::string token;
	float values[4] = { 0 };
	int i = 0;

	while( std::getline(iss, token, ' ') )
	{
		if( token.empty() != true )
		{
			values[i++] = (float )atof(token.c_str());
		}
	}

	return Vector4 { values[0], values[1], values[2], values[3] };
}

Vector2 Parser::ToVector2(std::string line)
{
	std::istringstream iss(line);
	std::string token;
	float values[3] = { 0 };
	int i = 0;

	while( std::getline(iss, token, ' ') )
	{
		if( token.empty() != true )
		{
			values[i++] = (float)atof(token.c_str());
		}
	}

	return Vector2 {values[0], values[1]};
}

Vector3 Parser::ToVector3(std::string line)
{
	std::istringstream iss(line);
	std::string token;
	float values[3] = { 0 };
	int i = 0;

	while( std::getline(iss,token,' '))
	{
		if( token.empty() != true )
		{
			values[i++] = (float)atof(token.c_str());
		}
	}

	return Vector3(values[0], values[1], values[2]);

}

float Parser::ToFloat(std::string line)
{
	return (float)atof(line.c_str());
}

int Parser::ToInt(std::string line)
{
	return (int)atoi(line.c_str());
}

float Parser::SciToFloat(std::string line)
{
	std::stringstream ss(line);
	float f = 0.0f;
	ss >> f;
	if( ss.fail() )
	{
		return 0;
	} 
	return(f);

}
