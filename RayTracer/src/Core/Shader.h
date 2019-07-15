#ifndef SHADER_H
#define SHADER_H

#include "Vector3.h"
#include "Ray.h"
#include "..//Entities/Material.h"
#include "..//Entities/PointLight.h"
#include "..//Entities/Primitive.h"

class Shader
{
public:

	Shader();
	~Shader();

	static Vector3 CalculateLighting(Material mat, std::vector<PointLight> pointLights);


private:
	Material _Material;

	std::vector<PointLight> _PointLights;
	Vector3 _AmbientLight;
	float _ShadowRayEpsilon;


	static Vector3 CalculateAmbient(Vector3 ambient);
	static Vector3 CalculateDiffuse(Vector3 diffuse, std::vector<PointLight> pointLights, Vector3 hitPoint, Vector3 normal);
	static Vector3 CalculateSpecular(Vector3 specular, float phongExponent);
	static Vector3 CalculateReflectance(Vector3 reflectance);

};


#endif 

