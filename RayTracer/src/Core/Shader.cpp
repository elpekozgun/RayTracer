#include "Shader.h"


Shader::Shader()
{

}

Shader::~Shader()
{

}

Vector3 Shader::CalculateLighting(std::vector<IGeometricEntity*> entities, Vector3 hitPoint, Vector3 normal, Vector3 eye, Material mat, std::vector<PointLight> pointLights, Vector3 ambientLight, float shadowRayEpsilon)
{
	Vector3 lightColor(0,0,0);

	for(auto& light : pointLights)
	{
		Vector3 lightDir = (light.Position - hitPoint).Normalized();
		float distance = (light.Position - hitPoint).Length();
		float Lambertian = fmaxf(normal.DotProduct(lightDir), 0.0f);


		Vector3 spec;
		Vector3 diff;
		if(Lambertian > 0)
		{
			//Vector3 h = (light.Position - hitPoint + eye - hitPoint).Normalized();
			//spec = light.Intensity * powf(normal.DotProductNormalized(h), mat.PhongExponent) / (distance * distance);
			Vector3 reflectDir = Reflect(lightDir , normal);
			spec = light.Intensity * powf(fmaxf(0.0f, (eye - hitPoint).DotProductNormalized(reflectDir)), mat.PhongExponent) / (distance * distance );
		}
		diff = light.Intensity * Lambertian / (distance * distance);

		Ray shadowRay(hitPoint + lightDir * shadowRayEpsilon, light.Position - hitPoint);

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

		auto color = mat.Diffuse * diff + mat.Specular * spec;

		lightColor += color;
	}

	return lightColor + ambientLight;
}

Vector3 Shader::Reflect(Vector3 lightDirection, Vector3 normal)
{
	return -lightDirection + normal * normal.DotProductNormalized(lightDirection) * 2.0f;
}

