#include "Shader.h"


Shader::Shader()
{

}

Shader::~Shader()
{

}

Vector3 Shader::CalculateLighting(Material mat, std::vector<PointLight> pointLights)
{
	return Vector3(); // CalculateAmbient(mat.Ambient) + CalculateDiffuse(mat.Diffuse, pointLights) + CalculateSpecular(mat.Specular, mat.PhongExponent) + CalculateReflectance(mat.MirrorReflectance);
}

Vector3 Shader::CalculateAmbient(Vector3 ambient)
{
	return ambient * 0.2f;
}

Vector3 Shader::CalculateDiffuse(Vector3 diffuse, std::vector<PointLight> pointLights, Vector3 hitPoint, Vector3 normal)
{
	for(auto& light : pointLights)
	{
		diffuse = light.Intensity * normal.DotProductNormalized(light.Position);
	}
	return Vector3();
}

Vector3 Shader::CalculateSpecular(Vector3 specular, float phongExponent)
{
	return Vector3();
}

Vector3 Shader::CalculateReflectance(Vector3 reflectance)
{
	return Vector3();
}
