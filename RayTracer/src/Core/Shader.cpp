#include "Shader.h"
#include "../GeometricEntities/Mesh.h"


Shader::Shader()
{

}

Shader::~Shader()
{

}

Vector3 Shader::CalculateLighting(std::vector<IGeometricEntity*> entities, Vector3 hitPoint, Vector3 normal, Vector3 eye, Material& mat, std::vector<PointLight> &pointLights, Vector3 ambientLight, float shadowRayEpsilon)
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

		
		Ray shadowRay(hitPoint + normal * shadowRayEpsilon, lightDir);
		float shadowT = 0;
		for(auto& entity : entities)
		{
			if(entity->Intersect(shadowRay) > 0)
			{
				diff = Vector3();
				spec = Vector3();
				break;
			}
		}

		/////////////////////////////////////////

		//float t = 0;
		//float tMin = INFINITY;
		//Ray ray(hitPoint,reflectDir);
		//for(auto& entity : entities)
		//{
		//	if(((Mesh*)entity)->GetType() == eEntityType::mesh)
		//	{
		//		auto mesh = dynamic_cast<Mesh*>(entity);
		//		for(auto& triangle : mesh->Triangles)
		//		{
		//			t = triangle.Intersect(ray);
		//			Vector3 hitpoint = ray.origin + ray.direction * t;
		//			if(t > 0 && t <= tMin)
		//			{
		//				tMin = t;
		//				Image.at(j).at(i) = Shader::CalculateLighting(GeometricEntities, hitpoint, triangle.GetNormal(hitpoint), camera.Position, mat, pointLights, ambientLight, shadowRayEpsilon);
		//			}
		//		}
		//	}
		//	else
		//	{
		//		t = entity->Intersect(ray);
		//		Vector3 hitpoint = ray.origin + ray.direction * t;
		//		if(t > 0 && t <= tMin)
		//		{
		//			tMin = t;
		//			closestObject = entity;
		//			Image.at(j).at(i) = Shader::CalculateLighting(GeometricEntities, hitpoint, entity->GetNormal(hitpoint), camera.Position, mat, pointLights, ambientLight, shadowRayEpsilon);
		//		}
		//	}
		//}
		

		auto color = mat.Diffuse * diff + mat.Specular * spec ;

		lightColor += color;
	}

	return lightColor + ambientLight * mat.Ambient;
}

Vector3 Shader::Reflect(Vector3 lightDirection, Vector3 normal)
{
	return -lightDirection + normal * normal.DotProductNormalized(lightDirection) * 2.0f;
}

