#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "Vector3.h"
#include "..//Entities/Primitive.h"
#include "..//Entities/IEntity.h"
#include "..//Entities/Camera.h"
#include "..//Entities/Material.h"
#include "..//Entities/VertexList.h"
#include "..//Entities/PointLight.h"
#include "..//GeometricEntities/IGeometricEntity.h"
#include "..//GeometricEntities/Mesh.h"
#include "..//GeometricEntities/Sphere.h"
#include "..//GeometricEntities/Triangle.h"


constexpr auto BACKGROUNDCOLOR		= "#BackgroundColor";
constexpr auto MAXRECURSIONDEPTH	= "#MaxRecursionDepth";
constexpr auto SHADOWRAYEPSILON		= "#ShadowRayEpsilon";
constexpr auto CAMERA				= "#Camera";
constexpr auto MATERIAL				= "#Material";
constexpr auto AMBIENTLIGHT			= "#AmbientLight";
constexpr auto POINTLIGHT			= "#PointLight";
constexpr auto VERTEXLIST			= "#VertexList";
constexpr auto SPHERE				= "#Sphere";
constexpr auto TRIANGLE				= "#Triangle";
constexpr auto MESH					= "#Mesh";


class Parser
{
public:
	Parser();
	~Parser();


	static std::vector<std::vector<std::string>> Parse(std::string path);
	static IEntity* GenerateEntity(std::vector<std::string> list);
	static IGeometricEntity* GenerateGeometricEntity(std::vector<std::string> list, VertexList& vertices);
	static void GeneratePPMfile(unsigned int width, unsigned int height, std::vector<std::vector<Vector3>> colorData);

private:
	static Vector2 ToVector2(std::string line);
	static Vector4 ToVector4(std::string line);
	static Vector3 ToVector3(std::string line);
	static float ToFloat(std::string line);
	static int ToInt(std::string line);
	static float SciToFloat(std::string line);

};

#endif 

