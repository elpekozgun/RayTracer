#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <omp.h>

#include "..//Entities/Camera.h"
#include "..//Entities/Material.h"
#include "..//Entities/Primitive.h"
#include "..//Entities/VertexList.h"
#include "..//GeometricEntities/IGeometricEntity.h"
#include "..////GeometricEntities/Mesh.h"
#include "Vector3.h"


class Renderer
{
public:

	Renderer(Camera& camera, Scene& scene, std::vector<IGeometricEntity*> entities, std::vector<Material> materials);
	~Renderer();

	void Render(std::vector<std::vector<Vector3>>& image);
	void RenderDistributed(std::vector<std::vector<Vector3>>& image, Vector3 focusPoint);

private:
	
	Camera _Camera;
	Scene _Scene;
	std::vector<IGeometricEntity*> _Entities;
	std::vector<Material> _Materials;


	Vector3 Trace(Ray& ray, int currentRecursion, bool includeAmbient);
	Vector3 GetColor(const IGeometricEntity* hitEntity, Vector3& hitPoint, Vector3& normal, const Material& mat);
	Vector3 Reflect(Vector3 lightDirection, Vector3 normal);
	Vector3 Refract(Vector3 incident, Vector3 normal, float refractiveIndex);
	float Fresnel(Vector3 incident, Vector3 normal, float refractiveIndex);
};


#endif 

