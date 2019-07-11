#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

IEntity* Parser::GenerateObject(std::vector<std::string> list)
{
	std::string header = list[0];

	if (header == BACKGROUNDCOLOR)
	{
		BackgroundColor* backgroundcolor = new	BackgroundColor();
		backgroundcolor->Color = ParseLineToVector3(list[1]);
		return backgroundcolor;
	}
	else if (header == MAXRECURSIONDEPTH)
	{
		MaxRecursionDepth* recursionDepth = new MaxRecursionDepth();
		recursionDepth->RecursionDepth = (float)atof(list[1].c_str());
		return recursionDepth;
	}
	else if (header == SHADOWRAYEPSILON)
	{
		ShadowRayEpsilon* shadowRayEpsilon = new ShadowRayEpsilon();
		shadowRayEpsilon->ShadowRayEpsilon= (float)atof(list[1].c_str());
		return shadowRayEpsilon;
	}
	else if (header == CAMERA)
	{
		Camera* camera = new Camera();
		camera->Position = ParseLineToVector3(list[1]);
		camera->Gaze = ParseLineToVector3(list[2]);
		camera->Up = ParseLineToVector3(list[3]);
		camera->NearPlane = ParseLineToVector4(list[4]);
		camera->NearDistance = (float)atof(list[5].c_str());
		camera->ScreenResolution = ParseLineToVector2(list[6]);

		return camera;
	}
	else if (header == MATERIAL)
	{
		Material* material = new Material();
		material->ID = atoi(list[1].c_str());
		material->Ambient = ParseLineToVector3(list[2]);
		material->Diffuse = ParseLineToVector3(list[3]);
		material->Specular = ParseLineToVector3(list[4]);
		material->PhongExponent = (float)atof(list[5].c_str());
		material->Specular = ParseLineToVector3(list[6]);

		return material;
	}
	else if (header == AMBIENTLIGHT)
	{
		AmbientLight* ambientLight = new AmbientLight();
		ambientLight->AmbientColor = ParseLineToVector3(list[1]);
		return ambientLight;
	}
	else if (header == POINTLIGHT)
	{
		PointLight* pointlight = new PointLight();
		pointlight->ID = atoi(list[1].c_str());
		pointlight->position = ParseLineToVector3(list[2]);
		pointlight->Intensity = ParseLineToVector3(list[3]);
		return pointlight;
	}
	else if (header == VERTEXLIST)
	{
		VertexList* vertexList = new VertexList();
		for (unsigned int i = 1; i < list.size(); i++)
		{
			vertexList->vertexList.push_back(ParseLineToVector3(list[i]));
		}
		return vertexList;
	}
	else if (header == SPHERE)
	{
	}
	else if (header == TRIANGLE)
	{

	}
	else if (header == MESH)
	{

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

Vector2 Parser::ParseLineToVector2(std::string line)
{
	std::string delimiter = " ";
	unsigned int pos = 0;
	std::string token;

	float vecVals[2] = { 0 };
	unsigned int i = 0;
	while ((pos = line.find(delimiter)) != std::string::npos)
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		float f = (float)std::atof(line.c_str());

		if (token != "")
		{
			vecVals[i] = f;
			i++;
		}
	}
	Vector2 retVal;
	retVal.x = vecVals[0];
	retVal.y = vecVals[1];

	return retVal;
}

Vector3 Parser::ParseLineToVector3(std::string line)
{
	std::string delimiter = " ";
	unsigned int pos = 0;
	std::string token;

	float vecVals[3] = { 0 };
	unsigned int i = 0;
	while ((pos = line.find(delimiter)) != std::string::npos)
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		float f = (float)std::atof(token.c_str());
		if (token != "")
		{
			vecVals[i] = f;
			i++;
		}
	}
	vecVals[2] = (float)std::atof(line.c_str());

	return Vector3(vecVals[0], vecVals[1], vecVals[2]);
}

Vector4 Parser::ParseLineToVector4(std::string line)
{
	std::string delimiter = " ";
	unsigned int pos = 0;
	std::string token;

	float vecVals[4] = { 0 };
	unsigned int i = 0;
	while ((pos = line.find(delimiter)) != std::string::npos)
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		float f = (float)std::atof(line.c_str());
		vecVals[i] = f;

		if (token != "")
		{
			vecVals[i] = f;
			i++;
		}
	}
	vecVals[3] = (float)std::atof(line.c_str());

	Vector4 retVal;
	retVal.x = vecVals[0];
	retVal.y = vecVals[1];
	retVal.z = vecVals[2];
	retVal.w = vecVals[3];

	return retVal;
}
