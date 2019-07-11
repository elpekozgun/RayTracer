#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Camera.h"
#include "Vector3.h"
#include "IEntity.h"
#include "..//GeometricEntities/IGeometricEntity.h"
#include "ValueType.h"
#include "Material.h"
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

	static IEntity* GenerateObject(std::vector<std::string> list);

	static std::vector<std::vector<std::string>> Parse(std::string path);

	static Vector3 GetVector3(std::vector<std::string> list);
	static Vector3 GetInt(std::vector<std::string> list);

private:
	static Vector2 ParseLineToVector2(std::string line);
	static Vector3 ParseLineToVector3(std::string line);
	static Vector4 ParseLineToVector4(std::string line);

};

#endif 

