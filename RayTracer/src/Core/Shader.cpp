#include "Shader.h"


Shader::Shader()
{

}

Shader::~Shader()
{

}

Vector3 Shader::CalculateLighting(IGeometricEntity* entity, Vector3 hitPoint, Vector3 normal, Vector3 eye, Material mat, std::vector<PointLight> pointLights, Vector3 ambientLight, float shadowRayEpsilon)
{
	Vector3 lightColor(0,0,0);

	for(auto& light : pointLights)
	{
		Vector3 lightDir = (light.Position - hitPoint).Normalized();
		float distance = (light.Position - hitPoint).Length();


		// Crap Method
		//Vector3 h = (light.Position - hitPoint + eye - hitPoint) / 2;
		//float spec = powf(normal.DotProductNormalized(h), mat.PhongExponent) * light.Intensity.X / (distance * distance);
		
		float diff = fmaxf(normal.DotProductNormalized(lightDir),0) * light.Intensity.X / (distance * distance);
		
		Vector3 reflectDir = Reflect(lightDir, normal);
		float spec = powf(eye.DotProductNormalized(reflectDir), mat.PhongExponent) * light.Intensity.X / (distance * distance);

		Ray shadowRay(hitPoint + lightDir * shadowRayEpsilon,light.Position);
		entity->Intersect(shadowRay);

		auto color = mat.Diffuse * diff  +  mat.Specular *  spec;

		lightColor = lightColor + color;
	}

	return lightColor + ambientLight;
}

Vector3 Shader::Reflect(Vector3 viewDirection, Vector3 normal)
{
	return normal * 2.0f * normal.DotProductNormalized(viewDirection) - viewDirection;
}

