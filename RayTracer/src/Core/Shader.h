#ifndef SHADER_H
#define SHADER_H

#include <cmath>

#include "Vector3.h"
#include "Ray.h"
#include "..//Entities/Material.h"
#include "..//Entities/PointLight.h"
#include "..//Entities/Primitive.h"
#include "..//GeometricEntities/IGeometricEntity.h"

class Shader
{
public:

	Shader();
	~Shader();

	static Vector3 CalculateLighting(int currentRecursion, std::vector<IGeometricEntity*> entities, Vector3 hitPoint, Vector3 normal, Vector3 eye, Material& mat, Scene& scene,bool includeAmbient);
	static Vector3 Reflect(Vector3 viewDirection, Vector3 normal);


private:


};


#endif 

