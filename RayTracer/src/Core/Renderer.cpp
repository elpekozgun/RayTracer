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
	auto start = std::chrono::high_resolution_clock::now();

#ifdef _OPENMP
#pragma omp parallel for
#endif
	for(unsigned int j = 0; j < (unsigned int)_Camera.ScreenResolution.y; j++)
	{
		for(unsigned int i = 0; i < (unsigned int)_Camera.ScreenResolution.x; i++)
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

	auto finish = std::chrono::high_resolution_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start) / 1e6;
	std::cout << "\nRendering finished in: " << seconds.count() << "seconds" << std::endl;

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
		rayColor = Vector3::Zero();
		Vector3 hitPoint = ray.origin + ray.direction * tMin;
		Vector3 normal = hitEntity->GetNormal(hitPoint);
		Vector3 reflectionColor = Vector3::Zero();
		Vector3 refractionColor = Vector3::Zero();


		// REFLECTION and REFRACTION
		if(currentRecursion < _Scene.RecursionDepth && mat.MirrorReflectance != Vector3::Zero())
		{			
			Vector3 reflectDir = Reflect(-ray.direction.Normalized(), normal);
			Ray reflectRay(hitPoint + reflectDir * _Scene.ShadowRayEpsilon, reflectDir);
			reflectionColor = Trace(reflectRay, ++currentRecursion, false) * mat.MirrorReflectance;

			float kr = Fresnel(ray.direction.Normalized(), normal, mat.Refraction);
			float kt = 1 - kr;
			bool outside = ray.direction.DotProductNormalized(normal) < 0;
			if(kr < 1)
			{
				Vector3 refractionDirection = Refract(ray.direction.Normalized(), normal, mat.Refraction);
				Vector3 refractionOrigin = outside ? hitPoint - normal * _Scene.ShadowRayEpsilon : hitPoint + normal * _Scene.ShadowRayEpsilon;
				Ray refractionRay = Ray(refractionOrigin, refractionDirection.Normalized());
				refractionColor = Trace(refractionRay, currentRecursion, false);
			}

			rayColor += (refractionColor * kt + reflectionColor * kr);

		}

		rayColor += GetColor(hitEntity, hitPoint, normal, mat);

		if(includeAmbient)
		{
			rayColor += _Scene.AmbientLight * mat.Ambient ;
		}
	}

	return rayColor;
}

Vector3 Renderer::GetColor(const IGeometricEntity* hitEntity, Vector3& hitPoint, Vector3& normal, const Material& mat)
{
	Vector3 color;

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

		// Shadows
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


	return color;
}

Vector3 Renderer::Reflect(Vector3 lightDirection, Vector3 normal)
{
	return -lightDirection + normal * normal.DotProductNormalized(lightDirection) * 2.0f;
}

Vector3 Renderer::Refract(Vector3 incident, Vector3 normal, float refractiveIndex)
{

	auto cosI = incident.Normalized().DotProduct(normal);
	float etaI = 1;
	float etaT = refractiveIndex;
	Vector3 n = normal;
	if(cosI < 0)
	{
		cosI = -cosI;
	}
	else
	{
		std::swap(etaI, etaT);
		n = -normal;
	}
	float eta = etaI / etaT;

	float k = 1 - eta * eta * (1 - cosI * cosI);
	return k < 0 ? Vector3::Zero() : incident.Normalized() * eta + n * (eta * cosI - sqrtf(k));
}

float Renderer::Fresnel(Vector3 incident, Vector3 normal, float refractiveIndex)
{

	auto cosI = incident.Normalized().DotProduct(normal);
	float kr = 0;
	float etaI = 1;
	float etaT = refractiveIndex;
	if(cosI > 0)
	{
		std::swap(etaI, etaT);
	}
	float sinT = etaI / etaT * sqrtf(std::max(0.0f, 1 - cosI * cosI));
	if(sinT >= 1)
	{
		kr = 1;
	}
	else
	{
		float cosT = sqrtf(std::max(0.0f, 1 - sinT *sinT));
		cosI = fabsf(cosI);
		float Rs = ((etaT * cosI) - (etaI * cosT)) / ((etaT * cosI) + (etaI * cosT));
		float Rp = ((etaI * cosI) - (etaT * cosT)) / ((etaI * cosI) + (etaT * cosT));
		kr	= (Rs * Rs + Rp * Rp) * 0.5f;
	}
	return kr;
}

