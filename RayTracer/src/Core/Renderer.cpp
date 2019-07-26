#include "Renderer.h"


Renderer::Renderer( Camera& camera, Scene& scene, std::vector<IGeometricEntity*> entities, std::vector<Material> materials)
{
_Camera = camera;
_Scene = scene;
_Entities = entities;
_Materials = materials;
}

Renderer::~Renderer()
{
}

void Renderer::Render(std::vector<std::vector<Vector3>>& image)
{
	for(unsigned int j = 0; j < _Camera.ScreenResolution.y; j++)
	{
		for(unsigned int i = 0; i < _Camera.ScreenResolution.x; i++)
		{
			Ray ray(_Camera.Position, _Camera.GetScreenPixel(i, j));
			image.at(j).at(i) = Trace
			(
				ray,
				0,
				true
			);
		}
	}
}

Vector3 Renderer::Trace(Ray& ray, int currentRecursion, bool includeAmbient)
{
	float tMin = INFINITY;
	int previousMatId = -1;
	Vector3 rayColor = _Scene.BackgroundColor;
	IGeometricEntity* hitEntity = NULL;
	Material mat;


	float t = 0;
	for(auto& entity : _Entities)
	{
		auto temp = entity->Intersect(ray);
		t = temp.first;
		if(t > 0 && t <= tMin)
		{
			int matId = entity->MaterialID();
			if(previousMatId != matId)
			{
				mat = *std::find_if(_Materials.begin(), _Materials.end(), [matId](Material& y) -> bool { return y.ID == matId; })._Ptr;
			}
			tMin = t;
			hitEntity = temp.second;
		}
	}

	if(hitEntity != NULL)
	{
		Vector3 hitPoint = ray.origin + ray.direction * tMin;
		Vector3 normal = hitEntity->GetNormal(hitPoint);

		// REFLECTION PART
		if(currentRecursion < _Scene.RecursionDepth && mat.MirrorReflectance != Vector3::Zero())
		{
			Vector3 reflectDir = Reflect(-ray.direction.Normalized(), normal);
			Ray reflectRay(hitPoint + reflectDir * _Scene.ShadowRayEpsilon, reflectDir);
			rayColor += Trace(reflectRay, currentRecursion++, false) * mat.MirrorReflectance;
		}

		// TODO: REFRACTIVE PART

		rayColor += GetColor(hitEntity, hitPoint, normal, mat);
	}

	return rayColor;
}

Vector3 Renderer::GetColor(IGeometricEntity* hitEntity, Vector3 hitPoint, Vector3 normal, Material mat)
{
	Vector3 color = _Scene.BackgroundColor;

	for(auto& light : _Scene.PointLights)
	{
		Vector3 lightDir = (light.Position - hitPoint).Normalized();
		Vector3 viewDir = (_Camera.Position - hitPoint).Normalized();
		Vector3 halfway = (lightDir + viewDir).Normalized();

		float distance = (light.Position - hitPoint).Length();
		float lambertian = fmaxf(normal.DotProduct(lightDir), 0.0f);

		Vector3	spec = light.Intensity * powf(normal.DotProductNormalized(halfway), mat.PhongExponent) / (distance * distance);
		Vector3	diff = light.Intensity * lambertian / (distance * distance);

		Ray shadowRay(hitPoint + lightDir * _Scene.ShadowRayEpsilon, lightDir);
		Ray negativeShadowRay(light.Position, -lightDir);

		bool IsIntersected = false;
		for(auto& entity : _Entities)
		{
			auto retVal = entity->Intersect(shadowRay);

			if(retVal.first > 0 && retVal.second != hitEntity)
			{
				diff = Vector3();
				spec = Vector3();
				break;
			}
		}

		color += mat.Diffuse * diff + mat.Specular * spec;
	}

	color += _Scene.AmbientLight * mat.Ambient;

	return color;
}

Vector3 Renderer::Reflect(Vector3 lightDirection, Vector3 normal)
{
	return -lightDirection + normal * normal.DotProductNormalized(lightDirection) * 2.0f;
}