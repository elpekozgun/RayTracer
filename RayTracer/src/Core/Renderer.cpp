#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(std::vector<std::vector<Vector3>>& image, Camera& camera, Scene& scene, std::vector<IGeometricEntity*> entities, std::vector<Material> materials)
{
	for(unsigned int j = 0; j < camera.ScreenResolution.y; j++)
	{
		for(unsigned int i = 0; i < camera.ScreenResolution.x; i++)
		{
			Ray ray(camera.Position, camera.GetScreenPixel(i, j));
			image.at(j).at(i) = Trace
			(
				ray, 
				camera.Position,
				0,
				scene,
				entities,
				materials,
				true
			);
		}
	}
}

Vector3 Renderer::Trace(Ray& ray, Vector3& view, int currentRecursion, Scene& scene, std::vector<IGeometricEntity*> entities, std::vector<Material> materials, bool includeAmbient)
{
	float tMin = INFINITY;
	int previousMatId = -1;
	Material mat;
	Vector3 rayColor = scene.BackgroundColor;
	IGeometricEntity* hitEntity = NULL;
	Vector3 reflectColor;
	Vector3 hitPoint;
	Vector3 normal;

	float t = 0;
	for(auto& entity : entities)
	{
		t = entity->Intersect(ray);
		if(t > 0 && t <= tMin)
		{
			int matId = entity->MaterialID();
			if(previousMatId != matId)
			{
				mat = *std::find_if(materials.begin(), materials.end(), [matId](Material& y) -> bool { return y.ID == matId; })._Ptr;
				previousMatId = matId;
			}

			tMin = t;
			hitEntity = entity;
		}
	}

	if(hitEntity != NULL)
	{

		hitPoint = ray.origin + ray.direction * tMin;
		normal = hitEntity->GetNormal(hitPoint).Normalized();
		
		for(auto& light : scene.PointLights)
		{
			Vector3 lightDir = (light.Position - hitPoint).Normalized();
			Vector3 viewDir = (view - hitPoint).Normalized();
			Vector3 halfway = (lightDir + viewDir).Normalized();


			float distance = (light.Position - hitPoint).Length();
			float lambertian = fmaxf(normal.DotProduct(lightDir), 0.0f);

			Vector3	spec = light.Intensity * powf(normal.DotProductNormalized(halfway), mat.PhongExponent) / (distance * distance);
			Vector3	diff = light.Intensity * lambertian / (distance * distance);

			Ray shadowRay(hitPoint + lightDir * scene.ShadowRayEpsilon, lightDir);
			float shadowT = 0;
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
			}

			rayColor = mat.Diffuse * diff + mat.Specular * spec;
		}

		if(includeAmbient)
		{
			rayColor += scene.AmbientLight * mat.Ambient;
		}
	}

	if(currentRecursion < scene.RecursionDepth)
	{
		Vector3 reflectDir = Shader::Reflect(-ray.direction, normal);
		Ray reflectRay(hitPoint + reflectDir * scene.ShadowRayEpsilon, reflectDir);
		rayColor += Trace(reflectRay, hitPoint , currentRecursion + 1 , scene, entities, materials, false) * mat.MirrorReflectance;
	}



	return rayColor;
		
		//if(t > 0 && t <= tMin)
		//{
		//	tMin = t;
		//	Vector3 hitPoint = ray.origin + ray.direction * t;
		//	Vector3 normal = entity->GetNormal(hitPoint).Normalized();
		//	Vector3	reflectDir = Shader::Reflect(-ray.direction, normal).Normalized();

		//	if(currentRecursion < scene.RecursionDepth)
		//	{
		//		Ray reflectionRay(hitPoint + reflectDir * scene.ShadowRayEpsilon, reflectDir);
		//		Vector3 reflectionColor = Trace(reflectionRay, reflectionRay.origin, ++currentRecursion, scene, entities, materials, false) * mat.MirrorReflectance;
		//		rayColor = reflectionColor;
		//	}
		//	rayColor = Shader::CalculateLighting(0, entities, hitPoint, normal, ray.origin , mat, scene, false);
		//}




}
