#include "Shader.h"
#include "../GeometricEntities/Mesh.h"


Shader::Shader()
{

}

Shader::~Shader()
{

}

constexpr int DEPTH = 3;

Vector3 Shader::CalculateLighting(std::vector<IGeometricEntity*> entities, Vector3 hitPoint, Vector3 normal, Vector3 eye, Material& mat, std::vector<PointLight> &pointLights, Vector3 ambientLight, float shadowRayEpsilon, Vector3 backgroundColor, int recursionDepth)
{
	Vector3 lightColor(0,0,0);

	for(auto& light : pointLights)
	{
		Vector3 lightDir = (light.Position - hitPoint).Normalized();
		Vector3 viewDir = (eye - hitPoint).Normalized();
		Vector3 halfway = (lightDir + viewDir).Normalized();
		
		float distance = (light.Position - hitPoint).Length();
		float lambertian = fmaxf(normal.DotProduct(lightDir), 0.0f);
		Vector3 reflectDir = Reflect(lightDir , normal);

		Vector3	spec = light.Intensity * powf(normal.DotProductNormalized(halfway), mat.PhongExponent) / (distance * distance);
		Vector3	diff =  light.Intensity * lambertian / (distance * distance);

		
		Ray shadowRay(hitPoint + lightDir * shadowRayEpsilon, lightDir);
		Ray reflectionRay(hitPoint, reflectDir);
		float shadowT = 0;
		
		Vector3 reflectionColor;
		float t = 0;
		float tMin = INFINITY;
		for(auto& entity : entities)
		{
			if(entity->Intersect(shadowRay) > 0)
			{
				diff = Vector3();
				spec = Vector3();
				break;
			}

			//if(recursionDepth < DEPTH)
			//{
			//	t = entity->Intersect(reflectionRay);
			//	Vector3 hitpoint = reflectionRay.origin + reflectionRay.direction * t;
			//	if(t > 0 && t <= tMin)
			//	{
			//		tMin = t;
			//		reflectionColor = Shader::CalculateLighting(entities, hitpoint, entity->GetNormal(hitpoint), eye , mat, pointLights, ambientLight, shadowRayEpsilon, backgroundColor, ++recursionDepth);
			//	}
			//}
		}


		auto color = mat.Diffuse * diff + mat.Specular * spec + reflectionColor;

		lightColor += color;
	}

	return lightColor + ambientLight * mat.Ambient;
}

Vector3 Shader::Reflect(Vector3 lightDirection, Vector3 normal)
{
	return -lightDirection + normal * normal.DotProductNormalized(lightDirection) * 2.0f;
}

